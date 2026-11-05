/* 0x004413e0 — beNDMWMdlItem::vfunc_37: registers the item model's receiver through its info (+0x14) with the class table. */
#include "dw4/reflected.h"
extern "C" {
extern char DAT_0051cea8[];
int beMessenger_RegisterReceiverFromInfo(int, int, char *);
void Gap__Bec__beNDMWMdlItem__vfunc_37(beNDMWMdlItem *, int);
}
void Gap__Bec__beNDMWMdlItem__vfunc_37(beNDMWMdlItem *p0, int a1)
{
    beMessenger_RegisterReceiverFromInfo(p0->_messenger, a1, DAT_0051cea8);
}
