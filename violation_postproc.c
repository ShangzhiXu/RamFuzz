/*
 * violation_postproc.c — Format-agnostic violation post-processor
 *                        WITHOUT coverage feedback (random selection).
 *
 * Field offsets come from FormatFuzzer's parse tree (via field_collector).
 * Valid-value domains come from 04_type_values.json (via json_reader).
 *
 * Environment variables:
 *   VIOLATION_JSON     path to 04_type_values.json (required)
 *   VIOLATION_VERBOSE  enable verbose output
 *   VIOLATION_LOG      log file path (default: stderr)
 */

#include "violation_postproc.h"
#include "field_collector.h"
#include "json_reader.h"
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <stdio.h>
#include <math.h>
#include <unistd.h>
#include <ctype.h>

/* ================================================================
 * Configuration
 * ================================================================ */

#define VIOLATION_PROB      0.5
#define GEO_BASE            (5.0/3.0)
#define MAX_FOUND           512
#define MAX_JSON_FIELDS     2048

/* ================================================================
 * Verbose logging
 * ================================================================ */

static int verbose = -1;
static FILE *vlog = NULL;
static void check_verbose(void) {
    if (verbose < 0) {
        verbose = (getenv("VIOLATION_VERBOSE") != NULL);
        if (verbose && !vlog) {
            const char *path = getenv("VIOLATION_LOG");
            if (path) vlog = fopen(path, "a");
            if (!vlog) vlog = stderr;
        }
    }
}
#define VLOG (vlog ? vlog : stderr)

/* ================================================================
 * Field collector globals (used by bt.h callback)
 * ================================================================ */

collected_field_t g_collected_fields[MAX_COLLECTED_FIELDS];
int               g_num_collected = -1;

void collector_start(void) { g_num_collected = 0; }
void collector_stop(void)  { }
void collector_record(unsigned min_off, unsigned max_off, const char *path) {
    if (g_num_collected < 0 || g_num_collected >= MAX_COLLECTED_FIELDS) return;
    collected_field_t *f = &g_collected_fields[g_num_collected];
    f->min_offset = min_off;
    f->max_offset = max_off;
    strncpy(f->path, path, MAX_FIELD_PATH_LEN - 1);
    f->path[MAX_FIELD_PATH_LEN - 1] = '\0';
    g_num_collected++;
}

/* ================================================================
 * JSON field table (loaded at init)
 * ================================================================ */

static json_field_t json_fields[MAX_JSON_FIELDS];
static int          json_nfields = 0;
static int          json_loaded = 0;
static int          initialized = 0;

/* ================================================================
 * Matched field: collected position + JSON domain info
 * ================================================================ */

typedef struct {
    unsigned    buf_offset;
    unsigned    field_size;
    int         json_idx;
} matched_field_t;

/* ================================================================
 * Path → JSON key matching (same as cov version)
 * ================================================================ */

static int path_to_json_key(const char *path, char *out, int maxlen) {
    const char *parts[32];
    int nparts = 0;
    const char *p = path;

    while (*p && nparts < 32) {
        parts[nparts++] = p;
        while (*p && *p != '~') p++;
        if (*p == '~') p++;
    }

    if (nparts < 2) return -1;

    int box_idx = -1;
    for (int i = nparts - 2; i >= 0; i--) {
        const char *part = parts[i];
        const char *end = (i + 1 < nparts) ? parts[i + 1] - 1 : path + strlen(path);
        int plen = (int)(end - part);

        if (plen > 6 && memcmp(part + plen - 6, "_block", 6) == 0) {
            box_idx = i; break;
        }
        if (plen > 4 && memcmp(part + plen - 4, "_box", 4) == 0) {
            box_idx = i; break;
        }
    }

    if (box_idx < 0 || box_idx >= nparts - 1) return -1;

    const char *box_part = parts[box_idx];
    const char *box_end = (box_idx + 1 < nparts) ? parts[box_idx + 1] - 1 : path + strlen(path);
    int box_len = (int)(box_end - box_part);

    char box_name[64];
    if (box_len > 6 && memcmp(box_part + box_len - 6, "_block", 6) == 0)
        box_len -= 6;
    else if (box_len > 4 && memcmp(box_part + box_len - 4, "_box", 4) == 0)
        box_len -= 4;
    if (box_len >= 64) box_len = 63;
    memcpy(box_name, box_part, box_len);
    box_name[box_len] = '\0';

    /* Pick the field name component after the box.
       Path examples:
         ...~mvhd_block~uint32_class~timescale   -> want "timescale"
         ...~mvhd_block~fp32_class~rate           -> want "rate"
         ...~mvhd_block~matrix~matrix_structure~fp32_class~a -> want "matrix_structure"
       Strategy: scan from box_idx+1 forward. Skip components ending in _class
       (type wrappers). The first non-_class component after the box is the field
       name we want. If it's a struct type name (no _class, no _block), take the
       NEXT component as the instance name (like matrix -> matrix_structure). */
    int field_idx = nparts - 1; /* fallback */
    for (int fi = box_idx + 1; fi < nparts; fi++) {
        const char *fp = parts[fi];
        const char *fe = (fi + 1 < nparts) ? parts[fi + 1] - 1 : path + strlen(path);
        int flen = (int)(fe - fp);
        int is_class = (flen > 6 && memcmp(fp + flen - 6, "_class", 6) == 0);
        if (!is_class) {
            /* This is either a direct field name (like "rate", "timescale")
               or a struct type name (like "matrix"). If the next component
               exists and is also not _class, use it (instance name). */
            if (fi + 1 < nparts) {
                const char *np = parts[fi + 1];
                const char *ne = (fi + 2 < nparts) ? parts[fi + 2] - 1 : path + strlen(path);
                int nlen = (int)(ne - np);
                int next_is_class = (nlen > 6 && memcmp(np + nlen - 6, "_class", 6) == 0);
                if (!next_is_class && fi + 2 < nparts) {
                    /* struct type + instance name pattern: use instance name */
                    field_idx = fi + 1;
                } else {
                    field_idx = fi;
                }
            } else {
                field_idx = fi;
            }
            break;
        } else if (fi + 1 < nparts) {
            /* _class wrapper: take the next component */
            field_idx = fi + 1;
            break;
        }
    }
    const char *field_part = parts[field_idx];
    const char *field_end = (field_idx + 1 < nparts) ? parts[field_idx + 1] - 1 : path + strlen(path);
    int field_len = (int)(field_end - field_part);
    char raw_key[128];
    snprintf(raw_key, sizeof(raw_key), "%s.%.*s", box_name, field_len, field_part);
    json_normalize_key(raw_key, out, maxlen);
    return 0;
}

/* ================================================================
 * Type helpers
 * ================================================================ */

static void get_type_range(const char *type_str, int64_t *lo, int64_t *hi) {
    if (strcmp(type_str, "uint8") == 0)  { *lo = 0; *hi = 255; return; }
    if (strcmp(type_str, "uint16") == 0) { *lo = 0; *hi = 65535; return; }
    if (strcmp(type_str, "uint24") == 0) { *lo = 0; *hi = 16777215; return; }
    if (strcmp(type_str, "uint32") == 0) { *lo = 0; *hi = 4294967295LL; return; }
    if (strcmp(type_str, "uint48") == 0) { *lo = 0; *hi = 281474976710655LL; return; }
    if (strcmp(type_str, "uint64") == 0) { *lo = 0; *hi = (int64_t)0x7FFFFFFFFFFFFFFFLL; return; }
    if (strcmp(type_str, "int8") == 0)   { *lo = -128; *hi = 127; return; }
    if (strcmp(type_str, "int16") == 0)  { *lo = -32768; *hi = 32767; return; }
    if (strcmp(type_str, "int32") == 0)  { *lo = -2147483648LL; *hi = 2147483647LL; return; }
    if (strcmp(type_str, "int64") == 0)  { *lo = (int64_t)0x8000000000000000LL; *hi = (int64_t)0x7FFFFFFFFFFFFFFFLL; return; }
    if (strcmp(type_str, "string") == 0) { *lo = 0; *hi = 4294967295LL; return; }
    *lo = 0; *hi = 255;
}

static int type_byte_size(const char *type_str) {
    if (strcmp(type_str, "uint8") == 0 || strcmp(type_str, "int8") == 0)   return 1;
    if (strcmp(type_str, "uint16") == 0 || strcmp(type_str, "int16") == 0) return 2;
    if (strcmp(type_str, "uint24") == 0)  return 3;
    if (strcmp(type_str, "uint32") == 0 || strcmp(type_str, "int32") == 0) return 4;
    if (strcmp(type_str, "uint48") == 0)  return 6;
    if (strcmp(type_str, "uint64") == 0 || strcmp(type_str, "int64") == 0) return 8;
    if (strcmp(type_str, "string") == 0)  return 4;
    return 0;
}

/* ================================================================
 * Random helpers
 * ================================================================ */

static double randf(void) {
    return (double)rand() / ((double)RAND_MAX + 1.0);
}

static int64_t rand_range(int64_t lo, int64_t hi) {
    if (lo >= hi) return lo;
    uint64_t span = (uint64_t)(hi - lo + 1);
    return lo + (int64_t)((uint64_t)rand() % span);
}

/* ================================================================
 * Violation value generation
 * ================================================================ */

static int64_t gen_violation_numeric(const json_field_t *jf) {
    int64_t t_lo, t_hi;
    get_type_range(jf->type_str, &t_lo, &t_hi);

    if (jf->domain_type == JSON_DT_RANGE && jf->dcnt >= 2) {
        int64_t d_lo = jf->dvals[0], d_hi = jf->dvals[1];
        int64_t below = (d_lo > t_lo) ? (d_lo - t_lo) : 0;
        int64_t above = (t_hi > d_hi) ? (t_hi - d_hi) : 0;
        int64_t total = below + above;
        if (total > 0) {
            int64_t pick = rand_range(0, total - 1);
            if (pick < below) return t_lo + pick;
            else return d_hi + 1 + (pick - below);
        }
        return t_lo;
    }

    if (jf->domain_type == JSON_DT_DISCRETE && jf->dcnt > 0) {
        for (int tries = 0; tries < 100; tries++) {
            int64_t v = rand_range(t_lo, t_hi);
            int found = 0;
            for (int j = 0; j < jf->dcnt; j++) {
                if (v == jf->dvals[j]) { found = 1; break; }
            }
            if (!found) return v;
        }
        return (jf->dvals[0] > t_lo) ? jf->dvals[0] - 1 : jf->dvals[0] + 1;
    }

    return rand_range(t_lo, t_hi);
}

static uint32_t gen_violation_fourcc(const json_field_t *jf) {
    for (int tries = 0; tries < 100; tries++) {
        char c[4];
        for (int j = 0; j < 4; j++)
            c[j] = (char)(0x20 + (rand() % 95));
        uint32_t v = ((uint32_t)(unsigned char)c[0] << 24) |
                     ((uint32_t)(unsigned char)c[1] << 16) |
                     ((uint32_t)(unsigned char)c[2] << 8)  |
                     ((uint32_t)(unsigned char)c[3]);
        int found = 0;
        for (int j = 0; j < jf->dcnt; j++) {
            if ((int64_t)v == jf->dvals[j]) { found = 1; break; }
        }
        if (!found) return v;
    }
    return 0xDEADBEEF;
}

/* ================================================================
 * Write value into buffer (big-endian)
 * ================================================================ */

static void write_val(uint8_t *buf, uint32_t off, uint8_t sz, int64_t val) {
    uint64_t uval = (uint64_t)val;
    for (int i = sz - 1; i >= 0; i--) {
        buf[off + i] = (uint8_t)(uval & 0xFF);
        uval >>= 8;
    }
}

/* ================================================================
 * Match collected fields against JSON
 * ================================================================ */

static int match_fields(matched_field_t *matched, int max_matched) {
    int nm = 0;
    for (int i = 0; i < g_num_collected && nm < max_matched; i++) {
        collected_field_t *cf = &g_collected_fields[i];
        int field_bytes = (int)(cf->max_offset - cf->min_offset + 1);
        if (field_bytes > 8 || field_bytes < 1) continue;

        char norm_key[JSON_MAX_KEY_LEN];
        if (path_to_json_key(cf->path, norm_key, JSON_MAX_KEY_LEN) < 0)
            continue;

        json_field_t *jf = json_find_field(json_fields, json_nfields, norm_key);
        if (!jf) continue;

        int expected_sz = type_byte_size(jf->type_str);
        if (expected_sz > 0 && expected_sz != field_bytes) continue;

        matched[nm].buf_offset = cf->min_offset;
        matched[nm].field_size = (unsigned)field_bytes;
        matched[nm].json_idx   = (int)(jf - json_fields);
        nm++;
    }
    return nm;
}

/* ================================================================
 * Random field selection (geometric cardinality, uniform random)
 * ================================================================ */

static int sample_cardinality(int n) {
    if (n <= 0) return 0;
    double u = randf();
    int k = (int)ceil(-log(1.0 - u) / log(GEO_BASE));
    if (k < 1) k = 1;
    if (k > n) k = n;
    return k;
}

static int select_fields_random(int nfound, int *selected, int max_sel) {
    if (nfound <= 0) return 0;
    int k = sample_cardinality(nfound);
    if (k > max_sel) k = max_sel;

    int *perm = (int*)malloc(nfound * sizeof(int));
    for (int i = 0; i < nfound; i++) perm[i] = i;
    for (int i = 0; i < k && i < nfound; i++) {
        int j = i + (rand() % (nfound - i));
        int tmp = perm[i]; perm[i] = perm[j]; perm[j] = tmp;
        selected[i] = perm[i];
    }
    free(perm);
    return k;
}

/* ================================================================
 * Public API
 * ================================================================ */

void violation_init(void) {
    if (initialized) return;
    srand((unsigned)time(NULL) ^ (unsigned)getpid());

    check_verbose();

    const char *json_path = getenv("VIOLATION_JSON");
    if (json_path) {
        json_nfields = json_read_fields(json_path, json_fields, MAX_JSON_FIELDS);
        if (json_nfields < 0) {
            fprintf(VLOG, "[violation] ERROR: failed to read %s\n", json_path);
            json_nfields = 0;
        } else {
            json_loaded = 1;
            if (verbose)
                fprintf(VLOG, "[violation] loaded %d violable fields from %s\n",
                        json_nfields, json_path);
        }
    } else {
        fprintf(VLOG, "[violation] WARNING: VIOLATION_JSON not set, no violations\n");
    }

    initialized = 1;
}

int violation_should_collect(void) {
    if (!initialized) violation_init();
    if (!json_loaded || json_nfields <= 0) return 0;
    return (randf() < VIOLATION_PROB) ? 1 : 0;
}

int violate_mp4_buffer(uint8_t *buf, uint32_t size) {
    if (!initialized) violation_init();
    check_verbose();
    if (!buf || size < 8) return 0;
    if (!json_loaded || json_nfields <= 0) return 0;

    if (randf() >= VIOLATION_PROB) {
        if (verbose) fprintf(VLOG, "[violation] skipped (prob)\n");
        return 0;
    }

    if (g_num_collected <= 0) {
        if (verbose) fprintf(VLOG, "[violation] no collected fields\n");
        return 0;
    }

    matched_field_t matched[MAX_FOUND];
    int nmatched = match_fields(matched, MAX_FOUND);
    if (nmatched == 0) {
        if (verbose) fprintf(VLOG, "[violation] no JSON matches\n");
        return 0;
    }

    if (verbose)
        fprintf(VLOG, "[violation] matched %d fields (from %d collected)\n",
                nmatched, g_num_collected);

    int selected[16];
    int k = select_fields_random(nmatched, selected, 16);

    int applied = 0;
    for (int i = 0; i < k; i++) {
        matched_field_t *mf = &matched[selected[i]];
        json_field_t *jf = &json_fields[mf->json_idx];

        if (mf->buf_offset + mf->field_size > size) continue;

        int is_fourcc = (jf->domain_type == JSON_DT_ENUM ||
                         strcmp(jf->type_str, "string") == 0);

        if (is_fourcc && mf->field_size == 4) {
            uint32_t v = gen_violation_fourcc(jf);
            if (verbose)
                fprintf(VLOG, "[violation] %s @%u: fourcc -> 0x%08x\n",
                        jf->key, mf->buf_offset, v);
            write_val(buf, mf->buf_offset, 4, (int64_t)v);
        } else {
            int64_t v = gen_violation_numeric(jf);
            if (verbose)
                fprintf(VLOG, "[violation] %s @%u: %d-byte -> %lld\n",
                        jf->key, mf->buf_offset, mf->field_size, (long long)v);
            write_val(buf, mf->buf_offset, mf->field_size, v);
        }
        applied++;
    }

    if (verbose) {
        fprintf(VLOG, "[violation] applied %d violations\n", applied);
        fflush(VLOG);
    }
    return applied;
}
