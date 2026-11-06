#include "dw4/reflected.h"
extern "C" {
extern char DAT_00516038[];
void beMessenger_RegisterReceiverFromInfo(int, int, char *);
void Gap__Bec__beNDMWMdlPlayer__vfunc_37(beNDMWMdlPlayer *, int, char *);
}
void Gap__Bec__beNDMWMdlPlayer__vfunc_37(beNDMWMdlPlayer * p0, int p1, char * p2)
{
    beMessenger_RegisterReceiverFromInfo(p0->_messenger, p1, DAT_00516038);
}
