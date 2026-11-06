#include "dw4/reflected.h"
extern "C" {
extern char DAT_0051dba0[];
void beMessenger_RegisterReceiverFromInfo(int, int, char *);
void Gap__Bec__beNDMWMdlMapBase__vfunc_37(beNDMWMdlMapBase *, int, char *);
}
void Gap__Bec__beNDMWMdlMapBase__vfunc_37(beNDMWMdlMapBase * p0, int p1, char * p2)
{
    beMessenger_RegisterReceiverFromInfo(p0->_messenger, p1, DAT_0051dba0);
}
