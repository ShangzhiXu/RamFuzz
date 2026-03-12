/*
 * violation_postproc_cov.c — Format-agnostic violation post-processor
 *                            with coverage feedback (paper method).
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
#include <sys/ipc.h>
#include <sys/shm.h>
#include <ctype.h>

/* ================================================================
 * Configuration
 * ================================================================ */

#define VIOLATION_PROB      0.5
#define EPSILON             0.1
#define GEO_BASE            0.6
#define COLD_START          50
#define MAX_FOUND           512
#define MAP_SIZE            65536
#define MAX_LAST_VIOLATED   16
#define ALPHA               0.5
#define LAMBDA              1.0
#define COV_WINDOW          100
#define FREQ_WINDOW         200
#define HIST_SIZE           200
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
int               g_num_collected = -1;  /* -1 = collection disabled */

void collector_start(void) {
    g_num_collected = 0;
}

void collector_stop(void) {
    /* leave g_num_collected as-is so violation code can read it */
}

void collector_record(unsigned min_off, unsigned max_off, const char *path) {
    if (g_num_collected < 0 || g_num_collected >= MAX_COLLECTED_FIELDS)
        return;
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

/* ================================================================
 * Matched field: collected position + JSON domain info
 * ================================================================ */

typedef struct {
    unsigned    buf_offset;  /* start byte in file buffer */
    unsigned    field_size;  /* bytes */
    int         json_idx;    /* index into json_fields[]  */
} matched_field_t;

/* ================================================================
 * Coverage feedback state (same as before)
 * ================================================================ */

typedef struct {
    int  fields[MAX_LAST_VIOLATED];
    int  nfields;
    int  new_edges;
} round_record_t;

static round_record_t history[HIST_SIZE];
static int      hist_head = 0;
static int      hist_count = 0;
static int      global_step = 0;
static int      initialized = 0;

static uint8_t *afl_area_ptr = NULL;
static uint8_t  virgin_bits[MAP_SIZE];

static int      pending_fields[MAX_LAST_VIOLATED];
static int      pending_nfields = 0;
static int      has_pending = 0;

/* ================================================================
 * Path → JSON key matching
 * ================================================================ */

/*
 * Extract "box.field" from parse tree path.
 * Path format: "file~mp4file~moov_block~mvhd_block~version"
 * Returns: "mvhd.version" (normalized)
 *
 * Strategy: find the last component ending with "_block" as the box,
 * use the component(s) after it as the field name.
 */
static int path_to_json_key(const char *path, char *out, int maxlen) {
    /* Split path by '~' */
    const char *parts[32];
    int nparts = 0;
    const char *p = path;

    while (*p && nparts < 32) {
        parts[nparts++] = p;
        while (*p && *p != '~') p++;
        if (*p == '~') p++;
    }

    if (nparts < 2) return -1;

    /* Find the last "_block" or "_box" parent */
    int box_idx = -1;
    for (int i = nparts - 2; i >= 0; i--) {
        const char *part = parts[i];
        /* Compute length of this part */
        const char *end = (i + 1 < nparts) ? parts[i + 1] - 1 : path + strlen(path);
        int plen = (int)(end - part);

        if (plen > 6 && memcmp(part + plen - 6, "_block", 6) == 0) {
            box_idx = i;
            break;
        }
        if (plen > 4 && memcmp(part + plen - 4, "_box", 4) == 0) {
            box_idx = i;
            break;
        }
    }

    if (box_idx < 0 || box_idx >= nparts - 1) return -1;

    /* Extract box name (strip _block / _box suffix) */
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

    /* Extract field name (last component) */
    const char *field_part = parts[nparts - 1];
    int field_len = (int)strlen(field_part);
    /* Remove trailing instance count like "_2" added by FormatFuzzer */
    /* Actually these are part of the name, skip for now */

    char raw_key[128];
    snprintf(raw_key, sizeof(raw_key), "%s.%s", box_name, field_part);

    /* Normalize */
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
    if (strcmp(type_str, "string") == 0) { *lo = 0; *hi = 4294967295LL; return; } /* FourCC */
    *lo = 0; *hi = 255;
}

static int type_byte_size(const char *type_str) {
    if (strcmp(type_str, "uint8") == 0 || strcmp(type_str, "int8") == 0)   return 1;
    if (strcmp(type_str, "uint16") == 0 || strcmp(type_str, "int16") == 0) return 2;
    if (strcmp(type_str, "uint24") == 0)  return 3;
    if (strcmp(type_str, "uint32") == 0 || strcmp(type_str, "int32") == 0) return 4;
    if (strcmp(type_str, "uint48") == 0)  return 6;
    if (strcmp(type_str, "uint64") == 0 || strcmp(type_str, "int64") == 0) return 8;
    if (strcmp(type_str, "string") == 0)  return 4; /* FourCC */
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
            if (pick < below)
                return t_lo + pick;
            else
                return d_hi + 1 + (pick - below);
        }
        return t_lo; /* fallback */
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
 * Coverage feedback
 * ================================================================ */

static int check_new_coverage(void) {
    if (!afl_area_ptr) return 0;
    int new_edges = 0;
    for (int i = 0; i < MAP_SIZE; i++) {
        uint8_t novel = afl_area_ptr[i] & virgin_bits[i];
        if (novel) {
            virgin_bits[i] &= ~afl_area_ptr[i];
            new_edges++;
        }
    }
    return new_edges;
}

static void record_round(void) {
    if (!has_pending) return;
    int new_edges = check_new_coverage();

    round_record_t *rec = &history[hist_head];
    rec->nfields = pending_nfields;
    memcpy(rec->fields, pending_fields, pending_nfields * sizeof(int));
    rec->new_edges = new_edges;

    hist_head = (hist_head + 1) % HIST_SIZE;
    if (hist_count < HIST_SIZE) hist_count++;

    if (verbose && new_edges > 0) {
        fprintf(VLOG, "[violation-cov] round recorded: %d new edges, %d fields\n",
                new_edges, pending_nfields);
        fflush(VLOG);
    }

    has_pending = 0;
    pending_nfields = 0;
}

/* ================================================================
 * Score computation (paper equations)
 * ================================================================ */

static void compute_scores(matched_field_t *found, int nfound, double *scores) {
    double cov_sum[MAX_JSON_FIELDS];
    int    cov_cnt[MAX_JSON_FIELDS];
    int    freq_cnt[MAX_JSON_FIELDS];
    int limit = json_nfields < MAX_JSON_FIELDS ? json_nfields : MAX_JSON_FIELDS;
    memset(cov_sum, 0, limit * sizeof(double));
    memset(cov_cnt, 0, limit * sizeof(int));
    memset(freq_cnt, 0, limit * sizeof(int));

    for (int step = 0; step < hist_count; step++) {
        int idx = (hist_head - 1 - step + HIST_SIZE * 2) % HIST_SIZE;
        round_record_t *rec = &history[idx];
        int in_cov  = (step < COV_WINDOW);
        int in_freq = (step < FREQ_WINDOW);
        if (!in_cov && !in_freq) break;

        for (int j = 0; j < rec->nfields; j++) {
            int fi = rec->fields[j];
            if (fi < 0 || fi >= json_nfields) continue;
            if (in_freq) freq_cnt[fi]++;
            if (in_cov && cov_cnt[fi] < COV_WINDOW) {
                double credit = (rec->nfields > 0)
                    ? (double)rec->new_edges / (double)rec->nfields : 0.0;
                cov_sum[fi] += credit;
                cov_cnt[fi]++;
            }
        }
    }

    for (int i = 0; i < nfound; i++) {
        int fi = found[i].json_idx;
        double cov_raw = (cov_cnt[fi] > 0) ? cov_sum[fi] / (double)cov_cnt[fi] : 0.0;
        double cov = 1.0 - exp(-LAMBDA * cov_raw);
        double freq = 1.0 / (double)(freq_cnt[fi] + 1);
        scores[i] = ALPHA * cov + (1.0 - ALPHA) * freq;
    }
}

/* ================================================================
 * Field selection (epsilon-greedy with coverage scores)
 * ================================================================ */

static int sample_cardinality(int n) {
    if (n <= 0) return 0;
    double u = randf();
    int k = (int)ceil(log(1.0 - u) / log(GEO_BASE));
    if (k < 1) k = 1;
    if (k > n) k = n;
    return k;
}

static int select_fields(matched_field_t *found, int nfound,
                         int *selected, int max_sel) {
    if (nfound <= 0) return 0;
    int k = sample_cardinality(nfound);
    if (k > max_sel) k = max_sel;
    global_step++;

    if (global_step <= COLD_START || randf() < EPSILON) {
        /* Random selection */
        int *perm = (int*)malloc(nfound * sizeof(int));
        for (int i = 0; i < nfound; i++) perm[i] = i;
        for (int i = 0; i < k && i < nfound; i++) {
            int j = i + (rand() % (nfound - i));
            int tmp = perm[i]; perm[i] = perm[j]; perm[j] = tmp;
            selected[i] = perm[i];
        }
        free(perm);
    } else {
        /* Exploit: rank by score */
        int *order = (int*)malloc(nfound * sizeof(int));
        double *scores = (double*)malloc(nfound * sizeof(double));
        compute_scores(found, nfound, scores);

        for (int i = 0; i < nfound; i++) order[i] = i;
        for (int i = 1; i < nfound; i++) {
            int key = order[i];
            double key_sc = scores[key];
            int j = i - 1;
            while (j >= 0 && scores[order[j]] < key_sc) {
                order[j+1] = order[j];
                j--;
            }
            order[j+1] = key;
        }
        for (int i = 0; i < k; i++)
            selected[i] = order[i];

        if (verbose && k > 0) {
            fprintf(VLOG, "[violation-cov] top score=%.4f (json_idx=%d)\n",
                    scores[order[0]], found[order[0]].json_idx);
        }

        free(order);
        free(scores);
    }
    return k;
}

/* ================================================================
 * Match collected fields against JSON
 * ================================================================ */

static int match_fields(matched_field_t *matched, int max_matched) {
    int nm = 0;
    for (int i = 0; i < g_num_collected && nm < max_matched; i++) {
        collected_field_t *cf = &g_collected_fields[i];
        int field_bytes = (int)(cf->max_offset - cf->min_offset + 1);

        /* Skip large entries (containers/boxes, not leaf fields) */
        if (field_bytes > 8 || field_bytes < 1) continue;

        /* Build JSON key from path */
        char norm_key[JSON_MAX_KEY_LEN];
        if (path_to_json_key(cf->path, norm_key, JSON_MAX_KEY_LEN) < 0)
            continue;

        /* Look up in JSON */
        json_field_t *jf = json_find_field(json_fields, json_nfields, norm_key);
        if (!jf) continue;

        /* Verify byte size matches type */
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
 * Public API
 * ================================================================ */

void violation_init(void) {
    if (initialized) return;
    srand((unsigned)time(NULL) ^ (unsigned)getpid());
    memset(history, 0, sizeof(history));
    memset(virgin_bits, 0xFF, sizeof(virgin_bits));
    hist_head = 0;
    hist_count = 0;
    pending_nfields = 0;
    has_pending = 0;
    global_step = 0;

    check_verbose();

    /* Load JSON */
    const char *json_path = getenv("VIOLATION_JSON");
    if (json_path) {
        json_nfields = json_read_fields(json_path, json_fields, MAX_JSON_FIELDS);
        if (json_nfields < 0) {
            fprintf(VLOG, "[violation-cov] ERROR: failed to read %s\n", json_path);
            json_nfields = 0;
        } else {
            json_loaded = 1;
            if (verbose)
                fprintf(VLOG, "[violation-cov] loaded %d violable fields from %s\n",
                        json_nfields, json_path);
        }
    } else {
        fprintf(VLOG, "[violation-cov] WARNING: VIOLATION_JSON not set, no violations\n");
    }

    /* Attach AFL++ SHM */
    char *shm_str = getenv("__AFL_SHM_ID");
    if (shm_str) {
        int shm_id = atoi(shm_str);
        void *ptr = shmat(shm_id, NULL, SHM_RDONLY);
        if (ptr != (void*)-1) {
            afl_area_ptr = (uint8_t*)ptr;
            if (verbose)
                fprintf(VLOG, "[violation-cov] attached to AFL++ SHM id=%d\n", shm_id);
        }
    }

    initialized = 1;
}

int violate_mp4_buffer(uint8_t *buf, uint32_t size) {
    if (!initialized) violation_init();
    check_verbose();
    if (!buf || size < 8) return 0;
    if (!json_loaded || json_nfields <= 0) return 0;

    /* Record previous round */
    record_round();

    /* Probabilistic skip */
    if (randf() >= VIOLATION_PROB) {
        check_new_coverage();
        if (verbose) fprintf(VLOG, "[violation-cov] skipped (prob)\n");
        return 0;
    }

    /* Check we have collected field data */
    if (g_num_collected <= 0) {
        if (verbose) fprintf(VLOG, "[violation-cov] no collected fields\n");
        return 0;
    }

    /* Match collected fields against JSON */
    matched_field_t matched[MAX_FOUND];
    int nmatched = match_fields(matched, MAX_FOUND);
    if (nmatched == 0) {
        if (verbose) fprintf(VLOG, "[violation-cov] no JSON matches\n");
        return 0;
    }

    if (verbose)
        fprintf(VLOG, "[violation-cov] matched %d fields (from %d collected)\n",
                nmatched, g_num_collected);

    /* Select fields */
    int selected[16];
    int k = select_fields(matched, nmatched, selected, 16);

    /* Apply violations */
    int applied = 0;
    pending_nfields = 0;

    for (int i = 0; i < k; i++) {
        matched_field_t *mf = &matched[selected[i]];
        json_field_t *jf = &json_fields[mf->json_idx];

        if (mf->buf_offset + mf->field_size > size) continue;

        int is_fourcc = (jf->domain_type == JSON_DT_ENUM ||
                         strcmp(jf->type_str, "string") == 0);

        if (is_fourcc && mf->field_size == 4) {
            uint32_t v = gen_violation_fourcc(jf);
            if (verbose)
                fprintf(VLOG, "[violation-cov] %s @%u: fourcc -> 0x%08x\n",
                        jf->key, mf->buf_offset, v);
            write_val(buf, mf->buf_offset, 4, (int64_t)v);
        } else {
            int64_t v = gen_violation_numeric(jf);
            if (verbose)
                fprintf(VLOG, "[violation-cov] %s @%u: %d-byte -> %lld\n",
                        jf->key, mf->buf_offset, mf->field_size, (long long)v);
            write_val(buf, mf->buf_offset, mf->field_size, v);
        }

        if (pending_nfields < MAX_LAST_VIOLATED)
            pending_fields[pending_nfields++] = mf->json_idx;

        applied++;
    }

    has_pending = (applied > 0);

    if (verbose) {
        fprintf(VLOG, "[violation-cov] applied %d violations\n", applied);
        fflush(VLOG);
    }
    return applied;
}
