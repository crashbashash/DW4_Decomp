/* src/game/beNDMWItemAbilityChip.c — the beNDMWItemAbilityChip methods
 *
 * One translation unit: 2 functions, in retail address order.  Folded
 * from the per-function units by tools/merge_units.py; the matching build
 * splits a function back out with tools/units.py, so `make check` still
 * verifies one function at a time. */
#include "dw4/reflected.h"
extern int g_beNDMWItemAbilityChip_metaObject[4];

/* 0x004486c0
 * Unpack a packed item word into the reflected fields: bits 0-9 are the
 * record number (_recNo), bit 10 the equipped flag (_isEquip) and bits 12-15
 * the kind number (_kindNo).  The same unpacking is shared by the sibling
 * beNDMWItem* classes (Weapon, Disk, ...); see docs/engine/item-database.md
 * for _recNo and docs/engine/typed-coverage.md for the field map. */
void Gap__Bec__beNDMWItemAbilityChip__vfunc_24(beNDMWItemAbilityChip *self, int packed) {
    self->_recNo = (int) (packed & 0x3FF);
    self->_isEquip = (char) ((packed & 0x400) != 0);
    self->_kindNo = (int) ((packed >> 0xC) & 0xF);
}

/* 0x00448f90
 * MetaObject accessor: returns the class's reflection handle (0x58bf48). */
int Gap__Bec__beNDMWItemAbilityChip__vfunc_20(void)
{
    return g_beNDMWItemAbilityChip_metaObject[0];
}
