#include "dw4/reflected.h"
extern "C" {
extern char DAT_005102a0[];
void beMessenger_RegisterReceiverFromInfo(int, int, char *);
void Gap__Bec__beDBManager__vfunc_29(beDBManager *, int, char *);
}
void Gap__Bec__beDBManager__vfunc_29(beDBManager *p0, int p1, char *p2)
{
    beMessenger_RegisterReceiverFromInfo(p0->_messenger, p1, DAT_005102a0);
}
