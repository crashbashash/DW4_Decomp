#include "dw4/reflected.h"
int Gap__Bec__beNDMWItemWeapon__vfunc_23(beNDMWItemWeapon *a) {
    int r = a->_recNo;
    r |= a->_isEquip ? 0x400 : 0;
    r |= a->_kindNo << 12;
    r |= a->_pocket << 16;
    r |= a->_revision << 20;
    return r;
}
