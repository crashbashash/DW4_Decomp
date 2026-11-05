#include "dw4/reflected.h"

/* 0x00149130
 * igPsx2Window vtable slot 42 (+0xa8): leaf that returns 0 and ignores the window, the PS2 backend's
 * "nothing to report" answer for an igWindow virtual (igWindow serialises no fields,
 * docs/engine/platform-seam.md).  Its neighbour is slot 41, 0x149170. */
int Gap__Core__igPsx2Window__vfunc_42(igPsx2Window *self) {
    return 0;
}
