/* beMatCtrl receiver registration. */
#include "dw4/reflected.h"
extern "C" int beMessenger_RegisterReceiver(int, int, int, int, int);
extern int MATCTRL[4];
extern "C" void Gap__Bec__beMatCtrl__vfunc_29(beMatCtrl *self, int selector)
{
    beMessenger_RegisterReceiver(self->_messenger, selector, (int)MATCTRL, 0, -1);
}
