#include "dw4/reflected.h"
extern int g_beNDMWItemYellowArmor_metaObject[4];

/* Inventory word layout shared by every beNDMWItem* subclass: bits 0-9 record number, bit 10
 * equipped flag, bits 12-15 item kind, and one subclass-specific field above that. The disk folder
 * stores its entries as (count << 16) | (0x4000 + type). */
#define ITEM_REC_NO_MASK 0x3FF
#define ITEM_EQUIPPED_BIT 0x400
#define ITEM_KIND_SHIFT 12
#define ITEM_KIND_MASK 0xF
#define ITEM_REVISION_SHIFT 20
#define ITEM_REVISION_MASK 0x7FF

/* Unpack an inventory word into this item's fields.  An armor's extra field is its _revision. */
void Gap__Bec__beNDMWItemYellowArmor__vfunc_24(beNDMWItemYellowArmor *self, int packed) {
    self->_recNo = (int) (packed & ITEM_REC_NO_MASK);
    self->_isEquip = (char) ((packed & ITEM_EQUIPPED_BIT) != 0);
    self->_kindNo = (int) ((packed >> ITEM_KIND_SHIFT) & ITEM_KIND_MASK);
    self->_revision = (int) ((packed >> ITEM_REVISION_SHIFT) & ITEM_REVISION_MASK);
}

int Gap__Bec__beNDMWItemYellowArmor__vfunc_20(void)
{
    return g_beNDMWItemYellowArmor_metaObject[0];
}
