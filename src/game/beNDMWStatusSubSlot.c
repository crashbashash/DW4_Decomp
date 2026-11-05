/* src/game/beNDMWStatusSubSlot.c — the beNDMWStatusSubSlot methods
 *
 * One translation unit: 10 functions, in retail address order.  Folded
 * from the per-function units by tools/merge_units.py; the matching build
 * splits a function back out with tools/units.py, so `make check` still
 * verifies one function at a time. */
#include "dw4/reflected.h"
/* A property record: the value sits at +12 (docs/engine/property-system.md, SYSgetPlayerLevel). */
typedef struct PropertyRecord { char pad0[12]; int value; } PropertyRecord;
extern int g_beNDMWStatusSubSlot_metaObject_0058af18[4];
extern char s_LEVEL_00519ff8[];
extern char s_LVPOINT_0051a000[];
/* Finds the object of the given class (metaObject) in an insight's object list; here the beNDMWStatus. */
int FUN_00236f80();
PropertyRecord *igProperty_GetRecord();
int beNDMWItemBase_GetRecordInt();
extern int g_beNDMWStatus_metaObject_0058b028[4];

/* 0x004176b0: reset the slot's state counters; st1 and st3 end up 1, st2 0
 * (the _st3 = 0 store is dead but is part of the retail sequence). */
void Gap__Bec__beNDMWStatusSubSlot__vfunc_25(beNDMWStatusSubSlot *self) {
    self->_st1 = 1;
    self->_st3 = 0;
    self->_st2 = 0;
    self->_st3 = 1;
}

/* 0x00417f40: true when the player's LEVEL is at least the LVPOINT record of
 * device folder entry `entryIndex` (record lookup via beNDMWItemBase_GetRecordInt;
 * the same check is in beNDMWStatusMainSlot). */
int Gap__Bec__beNDMWStatusSubSlot__vfunc_30(beNDMWStatusSubSlot *self, int entryIndex) {
    int playerLevel;
    int entry;
    int status;

    entry = *(int *)(((beNDMWItemBaseList *)self->_deviceFolder)->_data + (entryIndex * 4));
    status = FUN_00236f80(self->_insight, g_beNDMWStatus_metaObject_0058b028[0]);
    playerLevel = igProperty_GetRecord(self->_playerList, s_LEVEL_00519ff8)->value;
    return playerLevel >= beNDMWItemBase_GetRecordInt(entry, status, s_LVPOINT_0051a000);
}

/* 0x00417ff0: empty virtual slot (the sub-slot has no behaviour here) */
void Gap__Bec__beNDMWStatusSubSlot__vfunc_39(void)
{
}

/* 0x00418030: empty virtual slot (the sub-slot has no behaviour here) */
void Gap__Bec__beNDMWStatusSubSlot__vfunc_33(void)
{
}

/* 0x00418040: empty virtual slot (the sub-slot has no behaviour here) */
void Gap__Bec__beNDMWStatusSubSlot__vfunc_34(void)
{
}

/* 0x00418050: empty virtual slot (the sub-slot has no behaviour here) */
void Gap__Bec__beNDMWStatusSubSlot__vfunc_35(void)
{
}

/* 0x00418060: empty virtual slot (the sub-slot has no behaviour here) */
void Gap__Bec__beNDMWStatusSubSlot__vfunc_36(void)
{
}

/* 0x00418070: empty virtual slot (the sub-slot has no behaviour here) */
void Gap__Bec__beNDMWStatusSubSlot__vfunc_37(void)
{
}

/* 0x00418080: empty virtual slot (the sub-slot has no behaviour here) */
void Gap__Bec__beNDMWStatusSubSlot__vfunc_38(void)
{
}

/* 0x00423380: class meta-object handle getter */
int Gap__Bec__beNDMWStatusSubSlot__vfunc_20(void)
{
    return g_beNDMWStatusSubSlot_metaObject_0058af18[0];
}
