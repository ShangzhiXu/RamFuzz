#ifndef VIOLATION_POSTPROC_H
#define VIOLATION_POSTPROC_H

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

/* Initialize violation post-processor (call once, or auto-inits on first use) */
void violation_init(void);

/* Apply violation mutations to an MP4 buffer in-place.
 * Returns number of fields violated (0 if skipped). */
int violate_mp4_buffer(uint8_t* buf, uint32_t size);

#ifdef __cplusplus
}
#endif

#endif /* VIOLATION_POSTPROC_H */
