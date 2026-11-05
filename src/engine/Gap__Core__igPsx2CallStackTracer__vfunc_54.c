/* 0x003295a0
 * Constant getter in slot 54 of igPsx2CallStackTracer: returns 0x10000 (64 KiB).
 * It sits next to vfunc_53 (the 4 KiB page size) among the slots that describe the
 * address range the tracer pages over (vfunc_52/55/56); what the 64 KiB granule
 * is used for is not established. */
#include "dw4/reflected.h"
#define TRACER_BLOCK_SIZE 0x10000
int Gap__Core__igPsx2CallStackTracer__vfunc_54(igPsx2CallStackTracer *self) {
    return TRACER_BLOCK_SIZE;
}
