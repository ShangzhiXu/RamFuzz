#ifndef FIELD_COLLECTOR_H
#define FIELD_COLLECTOR_H

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

#define MAX_COLLECTED_FIELDS 2048
#define MAX_FIELD_PATH_LEN  256

typedef struct {
    unsigned min_offset;   /* start byte in file buffer */
    unsigned max_offset;   /* end byte (inclusive)      */
    char path[MAX_FIELD_PATH_LEN];
} collected_field_t;

extern collected_field_t g_collected_fields[];
extern int               g_num_collected;

void collector_start(void);
void collector_stop(void);
void collector_record(unsigned min_off, unsigned max_off, const char *path);

#ifdef __cplusplus
}
#endif

#endif
