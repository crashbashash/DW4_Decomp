#include "dw4/reflected.h"
extern "C" {
extern char DAT_005165c0[];
void beMessenger_RegisterReceiverFromInfo(int, int, char *);
void Gap__Bec__beNDMWMdlPlayer2__vfunc_37(beNDMWMdlPlayer2 *, int, char *);
}
void Gap__Bec__beNDMWMdlPlayer2__vfunc_37(beNDMWMdlPlayer2 * p0, int p1, char * p2)
{
    beMessenger_RegisterReceiverFromInfo(p0->_messenger, p1, DAT_005165c0);
}
