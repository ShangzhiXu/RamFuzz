/*
 * json_reader.c — Minimal JSON parser for 04_type_values.json
 *
 * Only handles the specific structure produced by G2FUZZ:
 *   { "box.field": { "type": "...", "values": { "discrete"|"range"|"enum": [...] } } }
 */

#include "json_reader.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

/* ---- helpers ---- */

static void skip_ws(const char **p) {
    while (**p && isspace((unsigned char)**p)) (*p)++;
}

static int parse_string(const char **p, char *out, int maxlen) {
    if (**p != '"') return -1;
    (*p)++;
    int i = 0;
    while (**p && **p != '"') {
        if (**p == '\\') {
            (*p)++;
            if (!**p) return -1;
        }
        if (i < maxlen - 1) out[i++] = **p;
        (*p)++;
    }
    out[i] = '\0';
    if (**p == '"') (*p)++;
    return 0;
}

static int parse_number(const char **p, int64_t *out) {
    char *end;
    *out = strtoll(*p, &end, 10);
    if (end == *p) return -1;
    *p = end;
    return 0;
}

static void skip_value(const char **p) {
    skip_ws(p);
    if (**p == '"') {
        (*p)++;
        while (**p && **p != '"') {
            if (**p == '\\') (*p)++;
            if (**p) (*p)++;
        }
        if (**p == '"') (*p)++;
    } else if (**p == '{') {
        int d = 1; (*p)++;
        while (**p && d > 0) {
            if (**p == '{') d++;
            else if (**p == '}') d--;
            else if (**p == '"') {
                (*p)++;
                while (**p && **p != '"') { if (**p == '\\') (*p)++; if (**p) (*p)++; }
            }
            if (**p) (*p)++;
        }
    } else if (**p == '[') {
        int d = 1; (*p)++;
        while (**p && d > 0) {
            if (**p == '[') d++;
            else if (**p == ']') d--;
            else if (**p == '"') {
                (*p)++;
                while (**p && **p != '"') { if (**p == '\\') (*p)++; if (**p) (*p)++; }
            }
            if (**p) (*p)++;
        }
    } else {
        while (**p && **p != ',' && **p != '}' && **p != ']' && !isspace((unsigned char)**p))
            (*p)++;
    }
}

/* ---- normalization ---- */

void json_normalize_key(const char *in, char *out, int maxlen) {
    int i = 0;
    int len = (int)strlen(in);
    /* Strip trailing underscores from the whole input first */
    while (len > 0 && in[len - 1] == '_') len--;
    for (int j = 0; j < len && i < maxlen - 1; j++) {
        char c = in[j];
        if (c == '.') {
            out[i++] = '.';
        } else if (c != '_') {
            out[i++] = (char)tolower((unsigned char)c);
        }
    }
    out[i] = '\0';
}

/* ---- type helpers ---- */

static int64_t type_max_val(const char *t) {
    if (strcmp(t, "uint8") == 0)  return 255;
    if (strcmp(t, "uint16") == 0) return 65535;
    if (strcmp(t, "uint24") == 0) return 16777215;
    if (strcmp(t, "uint32") == 0) return 4294967295LL;
    if (strcmp(t, "uint48") == 0) return 281474976710655LL;
    if (strcmp(t, "uint64") == 0) return (int64_t)0x7FFFFFFFFFFFFFFFLL;
    if (strcmp(t, "int8") == 0)   return 127;
    if (strcmp(t, "int16") == 0)  return 32767;
    if (strcmp(t, "int32") == 0)  return 2147483647LL;
    if (strcmp(t, "int64") == 0)  return (int64_t)0x7FFFFFFFFFFFFFFFLL;
    return 0;
}

static int64_t type_min_val(const char *t) {
    if (strncmp(t, "uint", 4) == 0) return 0;
    if (strcmp(t, "int8") == 0)  return -128;
    if (strcmp(t, "int16") == 0) return -32768;
    if (strcmp(t, "int32") == 0) return -2147483648LL;
    if (strcmp(t, "int64") == 0) return (int64_t)0x8000000000000000LL;
    return 0;
}

static int is_violable_type(const char *t) {
    return (strncmp(t, "uint", 4) == 0 && strlen(t) > 4 && atoi(t + 4) >= 8) ||
           strncmp(t, "int",  3) == 0 ||
           strcmp(t, "string") == 0;
}

static int is_full_range(const char *t, int dt, int64_t *dv, int dc) {
    if (dt != JSON_DT_RANGE || dc < 2) return 0;
    return (dv[0] <= type_min_val(t) && dv[1] >= type_max_val(t));
}

static uint32_t fourcc_from_str(const char *s) {
    unsigned char buf[4] = {' ', ' ', ' ', ' '};
    for (int i = 0; i < 4 && s[i]; i++)
        buf[i] = (unsigned char)s[i];
    return ((uint32_t)buf[0] << 24) | ((uint32_t)buf[1] << 16) |
           ((uint32_t)buf[2] << 8)  | (uint32_t)buf[3];
}

/* ---- main reader ---- */

int json_read_fields(const char *path, json_field_t *fields, int max_fields) {
    FILE *f = fopen(path, "r");
    if (!f) { fprintf(stderr, "[json_reader] cannot open %s\n", path); return -1; }

    fseek(f, 0, SEEK_END);
    long fsize = ftell(f);
    fseek(f, 0, SEEK_SET);
    char *buf = (char *)malloc(fsize + 1);
    if (!buf) { fclose(f); return -1; }
    fsize = (long)fread(buf, 1, fsize, f);
    buf[fsize] = '\0';
    fclose(f);

    const char *p = buf;
    int nfields = 0;

    skip_ws(&p);
    if (*p != '{') { free(buf); return -1; }
    p++;

    while (*p && nfields < max_fields) {
        skip_ws(&p);
        if (*p == '}') break;
        if (*p == ',') { p++; continue; }

        /* key */
        char key[JSON_MAX_KEY_LEN];
        if (parse_string(&p, key, JSON_MAX_KEY_LEN) < 0) break;

        skip_ws(&p);
        if (*p != ':') break;
        p++;
        skip_ws(&p);

        if (*p != '{') { skip_value(&p); continue; }
        p++; /* enter value object */

        char type_str[JSON_MAX_TYPE_LEN] = "";
        int domain_type = JSON_DT_NONE;
        int dcnt = 0;
        int64_t dvals[JSON_MAX_DVALS];
        char svals[JSON_MAX_DVALS][JSON_MAX_SVAL_LEN];
        memset(svals, 0, sizeof(svals));

        /* parse value object members */
        while (*p && *p != '}') {
            skip_ws(&p);
            if (*p == ',') { p++; continue; }
            if (*p == '}') break;

            char subkey[64];
            if (parse_string(&p, subkey, 64) < 0) break;
            skip_ws(&p);
            if (*p != ':') break;
            p++;
            skip_ws(&p);

            if (strcmp(subkey, "type") == 0) {
                parse_string(&p, type_str, JSON_MAX_TYPE_LEN);
            } else if (strcmp(subkey, "values") == 0) {
                if (*p != '{') { skip_value(&p); continue; }
                p++;

                while (*p && *p != '}') {
                    skip_ws(&p);
                    if (*p == ',') { p++; continue; }
                    if (*p == '}') break;

                    char vkey[32];
                    if (parse_string(&p, vkey, 32) < 0) break;
                    skip_ws(&p);
                    if (*p != ':') break;
                    p++;
                    skip_ws(&p);

                    if (strcmp(vkey, "discrete") == 0 && *p == '[') {
                        domain_type = JSON_DT_DISCRETE;
                        p++; dcnt = 0;
                        while (*p && *p != ']') {
                            skip_ws(&p);
                            if (*p == ',') { p++; continue; }
                            if (*p == ']') break;
                            int64_t val;
                            if (parse_number(&p, &val) < 0) break;
                            if (dcnt < JSON_MAX_DVALS) dvals[dcnt++] = val;
                            skip_ws(&p);
                        }
                        if (*p == ']') p++;
                    } else if (strcmp(vkey, "range") == 0 && *p == '[') {
                        domain_type = JSON_DT_RANGE;
                        p++; dcnt = 0;
                        while (*p && *p != ']') {
                            skip_ws(&p);
                            if (*p == ',') { p++; continue; }
                            if (*p == ']') break;
                            int64_t val;
                            if (parse_number(&p, &val) < 0) break;
                            if (dcnt < 2) dvals[dcnt++] = val;
                            skip_ws(&p);
                        }
                        if (*p == ']') p++;
                    } else if (strcmp(vkey, "enum") == 0 && *p == '[') {
                        domain_type = JSON_DT_ENUM;
                        p++; dcnt = 0;
                        while (*p && *p != ']') {
                            skip_ws(&p);
                            if (*p == ',') { p++; continue; }
                            if (*p == ']') break;
                            char sv[JSON_MAX_SVAL_LEN];
                            if (parse_string(&p, sv, JSON_MAX_SVAL_LEN) < 0) break;
                            if (dcnt < JSON_MAX_DVALS) {
                                strncpy(svals[dcnt], sv, JSON_MAX_SVAL_LEN - 1);
                                dvals[dcnt] = (int64_t)fourcc_from_str(sv);
                                dcnt++;
                            }
                            skip_ws(&p);
                        }
                        if (*p == ']') p++;
                    } else {
                        skip_value(&p);
                    }
                }
                if (*p == '}') p++;
            } else {
                skip_value(&p);
            }
        }
        if (*p == '}') p++;

        /* filter */
        if (!is_violable_type(type_str))  continue;
        if (domain_type == JSON_DT_NONE)  continue;
        if (is_full_range(type_str, domain_type, dvals, dcnt)) continue;

        json_field_t *jf = &fields[nfields];
        strncpy(jf->key, key, JSON_MAX_KEY_LEN - 1);
        jf->key[JSON_MAX_KEY_LEN - 1] = '\0';
        json_normalize_key(key, jf->norm_key, JSON_MAX_KEY_LEN);
        strncpy(jf->type_str, type_str, JSON_MAX_TYPE_LEN - 1);
        jf->domain_type = domain_type;
        jf->dcnt = dcnt;
        memcpy(jf->dvals, dvals, dcnt * sizeof(int64_t));
        if (domain_type == JSON_DT_ENUM)
            memcpy(jf->svals, svals, sizeof(jf->svals));
        nfields++;
    }

    free(buf);
    return nfields;
}

json_field_t *json_find_field(json_field_t *fields, int nfields, const char *norm_key) {
    /* Exact match first */
    for (int i = 0; i < nfields; i++) {
        if (strcmp(fields[i].norm_key, norm_key) == 0)
            return &fields[i];
    }
    /* Fallback: match just the field part (after '.') of both keys.
     * E.g. "file.entrycount" matches "ifd.entrycount" */
    const char *query_dot = strchr(norm_key, '.');
    if (query_dot) {
        const char *query_field = query_dot + 1;
        for (int i = 0; i < nfields; i++) {
            const char *jdot = strchr(fields[i].norm_key, '.');
            if (jdot && strcmp(jdot + 1, query_field) == 0)
                return &fields[i];
        }
    }
    return NULL;
}
