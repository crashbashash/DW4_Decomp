#include "dw4/reflected.h"
extern int g_beNDMWItemWeapon_metaObject[4];

/* Inventory word layout shared by every beNDMWItem* subclass: bits 0-9 record number, bit 10
 * equipped flag (a byte store), bits 12-15 item kind. A weapon adds two fields above that: bits
 * 16-19 the pocket and bits 20-30 the revision. */
#define ITEM_REC_NO_MASK 0x3FF
#define ITEM_EQUIPPED_BIT 0x400
#define ITEM_KIND_SHIFT 12
#define ITEM_KIND_MASK 0xF
#define ITEM_POCKET_SHIFT 16
#define ITEM_POCKET_MASK 0xF
#define ITEM_REVISION_SHIFT 20
#define ITEM_REVISION_MASK 0x7FF

/* Unpacks an inventory word into this item's reflected fields. */
void Gap__Bec__beNDMWItemWeapon__vfunc_24(beNDMWItemWeapon *self, int packed) {
    self->_recNo = (int) (packed & ITEM_REC_NO_MASK);
    self->_isEquip = (char) ((packed & ITEM_EQUIPPED_BIT) != 0);
    self->_kindNo = (int) ((packed >> ITEM_KIND_SHIFT) & ITEM_KIND_MASK);
    self->_pocket = (int) ((packed >> ITEM_POCKET_SHIFT) & ITEM_POCKET_MASK);
    self->_revision = (int) ((packed >> ITEM_REVISION_SHIFT) & ITEM_REVISION_MASK);
}

int Gap__Bec__beNDMWItemWeapon__vfunc_20(void)
{
    return g_beNDMWItemWeapon_metaObject[0];
}
