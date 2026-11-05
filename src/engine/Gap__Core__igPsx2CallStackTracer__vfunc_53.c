/* 0x00329590
 * Constant getter in slot 53 of igPsx2CallStackTracer: returns 0x1000, the 4 KiB
 * page size the tracer works in.  Evidence: vfunc_61 (src/unmatched) rounds a
 * request up with `(size + 0xFFF) >> 12` and walks the address range
 * (vfunc_52/55/56) one 0x1000 page at a time. */
#include "dw4/reflected.h"
#define TRACER_PAGE_SIZE 0x1000
int Gap__Core__igPsx2CallStackTracer__vfunc_53(igPsx2CallStackTracer *self) {
    return TRACER_PAGE_SIZE;
}
