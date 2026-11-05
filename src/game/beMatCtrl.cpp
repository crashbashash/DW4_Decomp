/* 0x0038b050 — beMatCtrl receiver registration. Findings #860.
 * Argument two remains in a1 and selects the registered receiver object;
 * m2c's first draft omitted it, shifting all later EE argument registers.
 * Verified byte-identical in C++ mode with the original compiler. */
#include "dw4/reflected.h"
extern "C" int beMessenger_RegisterReceiver(int, int, int, int, int);
extern int s_MATCTRL_0050ed58[4];
extern "C" void Gap__Bec__beMatCtrl__vfunc_29(beMatCtrl *self, int selector)
{
    beMessenger_RegisterReceiver(self->_messenger, selector, (int)s_MATCTRL_0050ed58, 0, -1);
}
