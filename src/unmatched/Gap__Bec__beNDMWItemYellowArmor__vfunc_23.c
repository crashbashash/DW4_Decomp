/* 0x004485d0 - 64 bytes. Flag word; asm nop in the else arm (retail pads both arms); alternate compiler -O3,p. */
#include "dw4/reflected.h"
int Gap__Bec__beNDMWItemYellowArmor__vfunc_23(beNDMWItemYellowArmor *arg0) {
    int v;
    int r = arg0->_recNo;
    if (arg0->_isEquip != 0) { v = 0x400; } else { v = 0; asm("nop"); /* matching construct: retail pads the else arm with a nop */ }
    r |= v;
    r |= arg0->_kindNo << 0xC;
    r |= arg0->_revision << 0x14;
    return r;
}
