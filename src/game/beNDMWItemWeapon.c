/* src/game/beNDMWItemWeapon.c — the beNDMWItemWeapon methods
 *
 * One translation unit: 2 functions, in retail address order.  Folded
 * from the per-function units by tools/merge_units.py; the matching build
 * splits a function back out with tools/units.py, so `make check` still
 * verifies one function at a time. */
#include "dw4/reflected.h"
extern int g_beNDMWItemWeapon_metaObject_0058bf60[4];

/* Inventory word layout shared by every beNDMWItem* subclass: bits 0-9 record
 * number, bit 10 equipped flag, bits 12-15 item kind (see beNDMWItemDisk.c;
 * finding #335: the equipped flag is a byte store).  A weapon adds two fields above that:
 * bits 16-19 the pocket and bits 20-30 the revision. */
#define ITEM_REC_NO_MASK 0x3FF
#define ITEM_EQUIPPED_BIT 0x400
#define ITEM_KIND_SHIFT 12
#define ITEM_KIND_MASK 0xF
#define ITEM_POCKET_SHIFT 16
#define ITEM_POCKET_MASK 0xF
#define ITEM_REVISION_SHIFT 20
#define ITEM_REVISION_MASK 0x7FF

/* 0x004483b0
 * Unpack an inventory word into this item's reflected fields. */
void Gap__Bec__beNDMWItemWeapon__vfunc_24(beNDMWItemWeapon *self, int packed) {
    self->_recNo = (int) (packed & ITEM_REC_NO_MASK);
    self->_isEquip = (char) ((packed & ITEM_EQUIPPED_BIT) != 0);
    self->_kindNo = (int) ((packed >> ITEM_KIND_SHIFT) & ITEM_KIND_MASK);
    self->_pocket = (int) ((packed >> ITEM_POCKET_SHIFT) & ITEM_POCKET_MASK);
    self->_revision = (int) ((packed >> ITEM_REVISION_SHIFT) & ITEM_REVISION_MASK);
}

/* 0x00448fc0
 * MetaObject accessor: returns the class's reflection handle (0x0058bf60). */
int Gap__Bec__beNDMWItemWeapon__vfunc_20(void)
{
    return g_beNDMWItemWeapon_metaObject_0058bf60[0];
}
