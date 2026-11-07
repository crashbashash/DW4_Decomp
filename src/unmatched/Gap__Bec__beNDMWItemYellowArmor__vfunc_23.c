#include "dw4/reflected.h"
int Gap__Bec__beNDMWItemYellowArmor__vfunc_23(beNDMWItemYellowArmor *arg0) {
    int v;
    int r = arg0->_recNo;
    if (arg0->_isEquip != 0) { v = 0x400; } else { v = 0; ; }
    r |= v;
    r |= arg0->_kindNo << 0xC;
    r |= arg0->_revision << 0x14;
    return r;
}
