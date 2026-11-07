#include "dw4/reflected.h"
extern "C" {
void beNDMWStatus_AssignEquipment(beNDMWStatusSubSlot *, int, int, int);
void Gap__Bec__beNDMWStatusSubSlot__vfunc_31(beNDMWStatusSubSlot *, char *, char *, char *);
}
extern "C" {
void FUN_00412600(beNDMWStatusSubSlot *, int, int, char *);
void Gap__Bec__beNDMWStatusSubSlot__vfunc_32(beNDMWStatusSubSlot *, char *, char *, int);
}

/* Equipment assignment for the sub slot. beNDMWStatus_AssignEquipment (equip by shared item
 * identity, toggle-off, chip-family exclusion) takes the slot list (_subSlot), the entry position
 * in it (_kindListPos) and the index chosen in the device folder (_retCode, bounds-checked against
 * the list at +120, _deviceFolder). The PowerSocket and MainSlot siblings have the same body. The
 * three arguments are unused. */
void Gap__Bec__beNDMWStatusSubSlot__vfunc_31(beNDMWStatusSubSlot *self, char *unusedArg1, char *unusedArg2, char *unusedArg3)
{
    beNDMWStatus_AssignEquipment(self, self->_subSlot, self->_kindListPos, self->_retCode);
}

/* Runs the shared helper FUN_00412600 (the DEVICE row selection step; -1 is its "no row" case)
 * over the sub slot's list at the current list position, passing the first argument through as the
 * row index. The other two arguments are unused. */
void Gap__Bec__beNDMWStatusSubSlot__vfunc_32(beNDMWStatusSubSlot *self, char *index, char *unusedArg2, int unusedArg3)
{
    FUN_00412600(self, self->_subSlot, self->_kindListPos, index);
}

/* A property record: the value sits at +12. */
typedef struct PropertyRecord { char pad0[12]; int value; } PropertyRecord;
extern "C" {
extern char LEVEL_3[];
extern char LVPOINT[];
/* Finds the object of the given class (metaObject) in an insight's object list; here the beNDMWStatus. */
int FUN_00236f80(int, int);
PropertyRecord *igProperty_GetRecord(int, char *);
int beNDMWItemBase_GetRecordInt(int, int, char *);
extern int g_beNDMWStatus_metaObject[4];

/* True when the player's LEVEL is at least the LVPOINT record of device folder entry `entryIndex`;
 * the same check is in beNDMWStatusMainSlot. */
int Gap__Bec__beNDMWStatusSubSlot__vfunc_30(beNDMWStatusSubSlot *self, int entryIndex) {
    int status;
    int entry;
    int playerLevel;

    entry = *(int *)(((beNDMWItemBaseList *)self->_deviceFolder)->_data + (entryIndex * 4));
    status = FUN_00236f80(self->_insight, g_beNDMWStatus_metaObject[0]);
    playerLevel = igProperty_GetRecord(self->_playerList, LEVEL_3)->value;
    return playerLevel >= beNDMWItemBase_GetRecordInt(entry, status, LVPOINT);
}
}
