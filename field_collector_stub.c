/*
 * field_collector_stub.c — Stub implementations for origin builds
 * that don't use violation but still link against bt.h which
 * references collector functions.
 */
#include "field_collector.h"
#include <string.h>

collected_field_t g_collected_fields[MAX_COLLECTED_FIELDS];
int               g_num_collected = -1;  /* -1 = disabled */

void collector_start(void) { g_num_collected = 0; }
void collector_stop(void)  { }
void collector_record(unsigned min_off, unsigned max_off, const char *path) {
    (void)min_off; (void)max_off; (void)path;
    /* no-op in origin build */
}
