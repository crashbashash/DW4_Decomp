#include "dw4/reflected.h"
extern "C" {
extern char DAT_0050e1f0[];
void beMessenger_RegisterReceiverFromInfo(int, int, char *);
void Gap__Bec__beCameraCtrl__vfunc_29(beCameraCtrl *, int, char *);
}
void Gap__Bec__beCameraCtrl__vfunc_29(beCameraCtrl * p0, int p1, char * p2)
{
    beMessenger_RegisterReceiverFromInfo(p0->_messenger, p1, DAT_0050e1f0);
}
