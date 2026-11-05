/* 0x0039cbc0: SELECTCTRL receiver registration, exact36 bytes; finding #914.
 * C mode tail-calls the helper (16 bytes); original C++ mode retains the frame.
 */
#include "dw4/reflected.h"
extern char D_0050f7f0[];
extern "C" void beMessenger_RegisterReceiverFromInfo(int, int, const char *);
extern "C" void beSelectCtrl_RegisterReceiver(beSelectCtrl *, int);
void beSelectCtrl_RegisterReceiver(beSelectCtrl *self, int info)
{
    beMessenger_RegisterReceiverFromInfo(self->_messenger, info, D_0050f7f0);
}
