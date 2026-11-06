/* Constant getter in slot 53 of igPsx2CallStackTracer: returns 0x1000, the 4 KiB page size the
 * tracer works in. */
#include "dw4/reflected.h"
#define TRACER_PAGE_SIZE 0x1000
int FUN_00329590(igPsx2CallStackTracer *self) {
    return TRACER_PAGE_SIZE;
}
