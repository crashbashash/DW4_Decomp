#include "dw4/reflected.h"
extern int g_beNDMWItemAbilityChip_metaObject[4];

/* Unpacks a packed item word into the reflected fields: bits 0-9 are the record number (_recNo),
 * bit 10 the equipped flag (_isEquip) and bits 12-15 the kind number (_kindNo). The sibling
 * beNDMWItem* classes (Weapon, Disk, ...) share the same unpacking. */
void Gap__Bec__beNDMWItemAbilityChip__vfunc_24(beNDMWItemAbilityChip *self, int packed) {
    self->_recNo = (int) (packed & 0x3FF);
    self->_isEquip = (char) ((packed & 0x400) != 0);
    self->_kindNo = (int) ((packed >> 0xC) & 0xF);
}

int Gap__Bec__beNDMWItemAbilityChip__vfunc_20(void)
{
    return g_beNDMWItemAbilityChip_metaObject[0];
}
