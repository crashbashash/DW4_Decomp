#include "dw4/reflected.h"
extern "C" {
extern char DAT_005194c0[];
void beMessenger_RegisterReceiverFromInfo(int, int, char *);
void Gap__Bec__beNDMWSaveCtrl__vfunc_29(beNDMWSaveCtrl *, int, char *);
}
void Gap__Bec__beNDMWSaveCtrl__vfunc_29(beNDMWSaveCtrl *p0, int p1, char *p2)
{
    beMessenger_RegisterReceiverFromInfo(p0->_messenger, p1, DAT_005194c0);
}
