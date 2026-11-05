/* Original transform-sequence interpolation fraction, 001df040. */
#ifndef DW4_SEQUENCEFRACTION_H
#define DW4_SEQUENCEFRACTION_H
#include <stdint.h>
/* IEEE binary32 bits. Caller supplies the selected adjacent key times.
 * Retail shifts each difference by 18, keeps its low unsigned 32 bits,
 * converts with EE rounding and divides. A sub-tick duration returns zero. */
uint32_t dw4_sequence_fraction(int64_t now,int64_t first,int64_t last);
/* 1bf7d0 compressed mode 0/3: wrap strictly after the authored cycle end. */
int64_t dw4_sequence_loop_clock(int64_t now,int64_t first,int64_t duration);
#endif
