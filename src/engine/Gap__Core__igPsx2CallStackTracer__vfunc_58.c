/* 0x003296d0
 * Constant-zero override in slot 58 of igPsx2CallStackTracer (`jr ra; move v0,zero`).
 * It ignores the tracer; no caller or meaning for the zero is recorded. */
#include "dw4/reflected.h"
int Gap__Core__igPsx2CallStackTracer__vfunc_58(igPsx2CallStackTracer *self) {
    return 0;
}
