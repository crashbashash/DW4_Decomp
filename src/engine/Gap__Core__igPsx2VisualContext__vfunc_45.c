#include "dw4/reflected.h"

/* igPsx2VisualContext vtable slot 45 (+0xb4): leaf that returns 0 and ignores the context, the PS2
 * backend's "nothing to report" answer for an igVisualContext virtual. */
int Gap__Core__igPsx2VisualContext__vfunc_45(igPsx2VisualContext *self) {
    return 0;
}
