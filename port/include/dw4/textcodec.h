#ifndef DW4_TEXTCODEC_H
#define DW4_TEXTCODEC_H
#include <stddef.h>
#include <stdint.h>
/* Retail 382eb0's custom USA/Japanese byte encoding, not UTF-8 or CP932.
 * Unknown codes are omitted; CR is ignored and LF needs two preceding codes.
 * NULL output queries the required count. Truncated pairs are safely omitted;
 * insufficient capacity fails before publishing any output. */
int dw4_textcodec_decode(const char *,size_t,uint32_t *,size_t,size_t *);
#endif
