/* src/game/beNDMWItemDisk.c — the beNDMWItemDisk methods
 *
 * One translation unit: 2 functions, in retail address order.  Folded
 * from the per-function units by tools/merge_units.py; the matching build
 * splits a function back out with tools/units.py, so `make check` still
 * verifies one function at a time. */
#include "dw4/reflected.h"
extern int g_beNDMWItemDisk_metaObject_0058bf38[4];

/* Inventory word layout shared by every beNDMWItem* subclass: bits 0-9 record
 * number, bit 10 equipped flag, bits 12-15 item kind, and one
 * subclass-specific field above that.  The disk folder stores its entries as
 * (count << 16) | (0x4000 + type) (finding #133; receiver fields: #539). */
#define ITEM_REC_NO_MASK 0x3FF
#define ITEM_EQUIPPED_BIT 0x400
#define ITEM_KIND_SHIFT 12
#define ITEM_KIND_MASK 0xF
#define ITEM_DISK_COUNT_SHIFT 16
#define ITEM_DISK_COUNT_MASK 0xF

/* 0x00448770 */
/* Unpack an inventory word into this item's fields.  A disk's extra field is its stack count (_kazu). */
void Gap__Bec__beNDMWItemDisk__vfunc_24(beNDMWItemDisk *self, int packed) {
    self->_recNo = (int) (packed & ITEM_REC_NO_MASK);
    self->_isEquip = (char) ((packed & ITEM_EQUIPPED_BIT) != 0);
    self->_kindNo = (int) ((packed >> ITEM_KIND_SHIFT) & ITEM_KIND_MASK);
    self->_kazu = (int) ((packed >> ITEM_DISK_COUNT_SHIFT) & ITEM_DISK_COUNT_MASK);
}

/* 0x00448f80 */
/* Reflection getter: returns the class's metaObject (the handle global that
 * beNDMWItem*_Register fills in). */
int Gap__Bec__beNDMWItemDisk__vfunc_20(void)
{
    return g_beNDMWItemDisk_metaObject_0058bf38[0];
}
