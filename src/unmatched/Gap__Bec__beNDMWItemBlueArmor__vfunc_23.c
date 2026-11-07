#include "dw4/reflected.h"
int Gap__Bec__beNDMWItemBlueArmor__vfunc_23(beNDMWItemBlueArmor *arg0) {
    int v;
    int r = arg0->_recNo;
    if (arg0->_isEquip != 0) { v = 0x400; } else { v = 0; ; }
    r |= v;
    r |= arg0->_kindNo << 0xC;
    r |= arg0->_pocket << 0x10;
    r |= arg0->_revision << 0x14;
    return r;
}
