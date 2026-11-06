#include "dw4/reflected.h"
extern "C" {
extern char DAT_0050ee78[];
void beMessenger_RegisterReceiverFromInfo(int, int, char *);
void Gap__Bec__beMeterCtrl__vfunc_29(beMeterCtrl *, int, char *);
}
void Gap__Bec__beMeterCtrl__vfunc_29(beMeterCtrl * p0, int p1, char * p2)
{
    beMessenger_RegisterReceiverFromInfo(p0->_messenger, p1, DAT_0050ee78);
}
