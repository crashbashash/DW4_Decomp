/* src/game/beNDMWStatusMainSlot.c - the beNDMWStatusMainSlot methods (main-equipment slot view
 * of the NDMW status screen), in retail address order.
 *
 * vfunc_30 is the equipment eligibility test: the item at a list index may be equipped when the
 * player's LEVEL property is at least the item's LVPOINT record (finding #803). Each function is matched on its own (tools/units.py). */
#include "dw4/reflected.h"
/* A property record: the value sits at +12 (docs/engine/property-system.md, SYSgetPlayerLevel). */
typedef struct PropertyRecord { char pad0[12]; int value; } PropertyRecord;
extern int g_beNDMWStatusMainSlot_metaObject_0058af20[4];
extern int g_beNDMWStatus_metaObject_0058b028[4];
extern char s_LEVEL_00519ff8[];
extern char s_LVPOINT_0051a000[];
/* Finds the object of the given class (metaObject) in an insight's object list; here the beNDMWStatus. */
int FUN_00236f80();
PropertyRecord *igProperty_GetRecord();
int beNDMWItemBase_GetRecordInt();

/* 0x00415870 - enter state 1; the later state levels restart at 0 */
void Gap__Bec__beNDMWStatusMainSlot__vfunc_25(beNDMWStatusMainSlot *self) {
    self->_st1 = 1;
    self->_st3 = 0;
    self->_st2 = 0;
}

/* 0x004164d0 - may the item at list index `index` be equipped: player LEVEL >= item LVPOINT */
int Gap__Bec__beNDMWStatusMainSlot__vfunc_30(beNDMWStatusMainSlot *self, int index) {
    int player_level;
    int item;
    int status;

    item = *(int *)(((beNDMWItemBaseList *)self->_deviceFolder)->_data + (index * 4));
    status = FUN_00236f80(self->_insight, g_beNDMWStatus_metaObject_0058b028[0]);
    player_level = igProperty_GetRecord(self->_playerList, s_LEVEL_00519ff8)->value;
    return player_level >= beNDMWItemBase_GetRecordInt(item, status, s_LVPOINT_0051a000);
}

/* 0x00423390 - class metaObject accessor */
int Gap__Bec__beNDMWStatusMainSlot__vfunc_20(void) {
    return g_beNDMWStatusMainSlot_metaObject_0058af20[0];
}
