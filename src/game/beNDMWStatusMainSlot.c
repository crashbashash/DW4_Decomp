/* Main-equipment slot view of the NDMW status screen. vfunc_30 is the equipment eligibility test:
 * the item at a list index may be equipped when the player's LEVEL property is at least the item's
 * LVPOINT record. */
#include "dw4/reflected.h"
/* A property record: the value sits at +12. */
typedef struct PropertyRecord { char pad0[12]; int value; } PropertyRecord;
extern int g_beNDMWStatusMainSlot_metaObject[4];
extern int g_beNDMWStatus_metaObject[4];
extern char LEVEL_3[];
extern char LVPOINT[];
/* Finds the object of the given class (metaObject) in an insight's object list; here the beNDMWStatus. */
int FUN_00236f80();
PropertyRecord *igProperty_GetRecord();
int beNDMWItemBase_GetRecordInt();

/* Enter state 1; the later state levels restart at 0 */
void Gap__Bec__beNDMWStatusMainSlot__vfunc_25(beNDMWStatusMainSlot *self) {
    self->_st1 = 1;
    self->_st3 = 0;
    self->_st2 = 0;
}

int Gap__Bec__beNDMWStatusMainSlot__vfunc_30(beNDMWStatusMainSlot *self, int index) {
    int player_level;
    int item;
    int status;

    item = *(int *)(((beNDMWItemBaseList *)self->_deviceFolder)->_data + (index * 4));
    status = FUN_00236f80(self->_insight, g_beNDMWStatus_metaObject[0]);
    player_level = igProperty_GetRecord(self->_playerList, LEVEL_3)->value;
    return player_level >= beNDMWItemBase_GetRecordInt(item, status, LVPOINT);
}

/* Class metaObject accessor */
int Gap__Bec__beNDMWStatusMainSlot__vfunc_20(void) {
    return g_beNDMWStatusMainSlot_metaObject[0];
}
