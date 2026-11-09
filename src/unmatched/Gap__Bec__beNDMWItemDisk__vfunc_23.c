#include "dw4/reflected.h"

int Gap__Bec__beNDMWItemDisk__vfunc_23(beNDMWItemDisk *self) {
    int packed = self->_recNo;
    packed |= self->_isEquip ? 0x400 : 0;
    packed |= self->_kindNo << 12;
    packed |= self->_kazu << 16;
    return packed;
}
