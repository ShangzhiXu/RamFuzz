#ifndef VIOLATION_POSTPROC_H
#define VIOLATION_POSTPROC_H

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

/* Initialize violation post-processor (call once, or auto-inits on first use) */
void violation_init(void);

/* Returns 1 if this round should collect fields and apply violation, 0 to skip.
 * Uses VIOLATION_PROB to decide probabilistically. */
int violation_should_collect(void);

/* Apply violation mutations to a file buffer in-place.
 * Returns number of fields violated (0 if skipped). */
int violate_buffer(uint8_t* buf, uint32_t size);

#ifdef __cplusplus
}
#endif

#endif /* VIOLATION_POSTPROC_H */
