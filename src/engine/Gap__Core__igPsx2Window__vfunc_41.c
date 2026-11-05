#include "dw4/reflected.h"

/* 0x00149170
 * igPsx2Window vtable slot 41 (+0xa4): leaf that returns 0 and ignores the window, the PS2 backend's
 * "nothing to report" answer for an igWindow virtual (igWindow serialises no fields,
 * docs/engine/platform-seam.md).  Its neighbour is slot 42, 0x149130. */
int Gap__Core__igPsx2Window__vfunc_41(igPsx2Window *self) {
    return 0;
}
