#include "dw4/reflected.h"
extern int g_beNDMWItemDisk_metaObject[4];

/* Inventory word layout shared by every beNDMWItem* subclass: bits 0-9 record number, bit 10
 * equipped flag, bits 12-15 item kind, and one subclass-specific field above that. The disk folder
 * stores its entries as (count << 16) | (0x4000 + type). */
#define ITEM_REC_NO_MASK 0x3FF
#define ITEM_EQUIPPED_BIT 0x400
#define ITEM_KIND_SHIFT 12
#define ITEM_KIND_MASK 0xF
#define ITEM_DISK_COUNT_SHIFT 16
#define ITEM_DISK_COUNT_MASK 0xF

/* Unpack an inventory word into this item's fields.  A disk's extra field is its stack count (_kazu). */
void Gap__Bec__beNDMWItemDisk__vfunc_24(beNDMWItemDisk *self, int packed) {
    self->_recNo = (int) (packed & ITEM_REC_NO_MASK);
    self->_isEquip = (char) ((packed & ITEM_EQUIPPED_BIT) != 0);
    self->_kindNo = (int) ((packed >> ITEM_KIND_SHIFT) & ITEM_KIND_MASK);
    self->_kazu = (int) ((packed >> ITEM_DISK_COUNT_SHIFT) & ITEM_DISK_COUNT_MASK);
}

int Gap__Bec__beNDMWItemDisk__vfunc_20(void)
{
    return g_beNDMWItemDisk_metaObject[0];
}
