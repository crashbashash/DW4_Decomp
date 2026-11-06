#include "dw4/reflected.h"
/* A property record: the value sits at +12. */
typedef struct PropertyRecord { char pad0[12]; int value; } PropertyRecord;
extern int g_beNDMWStatusSubSlot_metaObject[4];
extern char LEVEL_3[];
extern char LVPOINT[];
/* Finds the object of the given class (metaObject) in an insight's object list; here the beNDMWStatus. */
int FUN_00236f80();
PropertyRecord *igProperty_GetRecord();
int beNDMWItemBase_GetRecordInt();
extern int g_beNDMWStatus_metaObject[4];

/* Resets the slot's state counters; st1 and st3 end up 1, st2 0 (the _st3 = 0 store is dead but
 * kept). */
void Gap__Bec__beNDMWStatusSubSlot__vfunc_25(beNDMWStatusSubSlot *self) {
    self->_st1 = 1;
    self->_st3 = 0;
    self->_st2 = 0;
    self->_st3 = 1;
}

/* True when the player's LEVEL is at least the LVPOINT record of device folder entry `entryIndex`;
 * the same check is in beNDMWStatusMainSlot. */
int Gap__Bec__beNDMWStatusSubSlot__vfunc_30(beNDMWStatusSubSlot *self, int entryIndex) {
    int playerLevel;
    int entry;
    int status;

    entry = *(int *)(((beNDMWItemBaseList *)self->_deviceFolder)->_data + (entryIndex * 4));
    status = FUN_00236f80(self->_insight, g_beNDMWStatus_metaObject[0]);
    playerLevel = igProperty_GetRecord(self->_playerList, LEVEL_3)->value;
    return playerLevel >= beNDMWItemBase_GetRecordInt(entry, status, LVPOINT);
}

void Gap__Bec__beNDMWStatusSubSlot__vfunc_39(void)
{
}

void Gap__Bec__beNDMWStatusSubSlot__vfunc_33(void)
{
}

void Gap__Bec__beNDMWStatusSubSlot__vfunc_34(void)
{
}

void Gap__Bec__beNDMWStatusSubSlot__vfunc_35(void)
{
}

void Gap__Bec__beNDMWStatusSubSlot__vfunc_36(void)
{
}

void Gap__Bec__beNDMWStatusSubSlot__vfunc_37(void)
{
}

void Gap__Bec__beNDMWStatusSubSlot__vfunc_38(void)
{
}

/* Class meta-object handle getter */
int Gap__Bec__beNDMWStatusSubSlot__vfunc_20(void)
{
    return g_beNDMWStatusSubSlot_metaObject[0];
}
