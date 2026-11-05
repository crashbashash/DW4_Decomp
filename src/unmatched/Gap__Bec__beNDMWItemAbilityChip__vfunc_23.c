#include "dw4/reflected.h"
int Gap__Bec__beNDMWItemAbilityChip__vfunc_23(beNDMWItemAbilityChip *arg0) {
    int a = arg0->_recNo;
    int v;
    if (arg0->_isEquip != 0) {
        v = 0x400;
    } else {
        v = 0;
    }
    a = a | v;
    a = a | (arg0->_kindNo << 0xC);
    return a;
}
