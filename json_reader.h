#ifndef JSON_READER_H
#define JSON_READER_H

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

#define JSON_MAX_DVALS    64
#define JSON_MAX_KEY_LEN  64
#define JSON_MAX_TYPE_LEN 16
#define JSON_MAX_SVAL_LEN 8

#define JSON_DT_NONE     0
#define JSON_DT_DISCRETE 1
#define JSON_DT_RANGE    2
#define JSON_DT_ENUM     3

typedef struct {
    char    key[JSON_MAX_KEY_LEN];       /* original: "mvhd.version"        */
    char    norm_key[JSON_MAX_KEY_LEN];  /* normalized: "mvhd.version"      */
    char    type_str[JSON_MAX_TYPE_LEN]; /* "uint8", "uint32", "string" ... */
    int     domain_type;                 /* JSON_DT_DISCRETE / RANGE / ENUM */
    int     dcnt;                        /* number of valid values          */
    int64_t dvals[JSON_MAX_DVALS];       /* discrete/range values, or FourCC as uint32 for enum */
    char    svals[JSON_MAX_DVALS][JSON_MAX_SVAL_LEN]; /* string enum values */
} json_field_t;

/*
 * Read 04_type_values.json. Returns count of violable fields, -1 on error.
 * Fields with full type range are automatically filtered out.
 */
int json_read_fields(const char *path, json_field_t *fields, int max_fields);

/*
 * Find field by normalized key. Returns pointer or NULL.
 */
json_field_t *json_find_field(json_field_t *fields, int nfields, const char *norm_key);

/*
 * Normalize: lowercase, remove underscores, keep dots.
 */
void json_normalize_key(const char *in, char *out, int maxlen);

#ifdef __cplusplus
}
#endif

#endif
