#include "dw4/reflected.h"
extern "C" {
extern char DAT_00515e28[];
void beMessenger_RegisterReceiverFromInfo(int, int, char *);
void Gap__Bec__beNDMWMdlEnemy__vfunc_37(beNDMWMdlEnemy *, int, char *);
}
void Gap__Bec__beNDMWMdlEnemy__vfunc_37(beNDMWMdlEnemy * p0, int p1, char * p2)
{
    beMessenger_RegisterReceiverFromInfo(p0->_messenger, p1, DAT_00515e28);
}
