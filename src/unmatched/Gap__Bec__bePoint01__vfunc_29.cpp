#include "dw4/reflected.h"
extern "C" {
extern char DAT_0050f6e0[];
void beMessenger_RegisterReceiverFromInfo(int, int, char *);
void Gap__Bec__bePoint01__vfunc_29(bePoint01 *, int, char *);
}
void Gap__Bec__bePoint01__vfunc_29(bePoint01 * p0, int p1, char * p2)
{
    beMessenger_RegisterReceiverFromInfo(p0->_messenger, p1, DAT_0050f6e0);
}
