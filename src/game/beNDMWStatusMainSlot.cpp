/* Two slots of the status screen's main slot that forward to the equipment procedures with the
 * current pocket (`_apuPocket`), the cursor position in it (`_pocketPos`) and one more argument. */
#include "dw4/reflected.h"
extern "C" {
/* Equipment procedure of the status screen; the last argument is passed through
 * from the vfunc_39 caller (DEVICE). */
void FUN_00412600(int slot, int pocket, int pocketPos, char *extra);
void Gap__Bec__beNDMWStatusMainSlot__vfunc_39(beNDMWStatusMainSlot *, char *, char *, int);
}
extern "C" {
/* Equipment assignment of the status screen; the last argument is the slot's `_retCode`. */
void beNDMWStatus_AssignEquipment(int slot, int pocket, int pocketPos, int retCode);
void Gap__Bec__beNDMWStatusMainSlot__vfunc_37(beNDMWStatusMainSlot *, char *, char *, char *);
}

/* Only the first argument is used. */
void Gap__Bec__beNDMWStatusMainSlot__vfunc_39(beNDMWStatusMainSlot * self, char * extra, char * unusedA, int unusedB)
{
    /* matching construct: (int) cast because the callee takes the receiver as an int */
    FUN_00412600((int)self, self->_apuPocket, self->_pocketPos, extra);
}

/* All three arguments are unused. */
void Gap__Bec__beNDMWStatusMainSlot__vfunc_37(beNDMWStatusMainSlot * self, char * unusedA, char * unusedB, char * unusedC)
{
    /* matching construct: (int) cast because the callee takes the receiver as an int */
    beNDMWStatus_AssignEquipment((int)self, self->_apuPocket, self->_pocketPos, self->_retCode);
}

/* A property record: the value sits at +12. */
typedef struct PropertyRecord { char pad0[12]; int value; } PropertyRecord;
extern "C" {
extern int g_beNDMWStatus_metaObject[4];
extern char LEVEL_3[];
extern char LVPOINT[];
/* Finds the object of the given class (metaObject) in an insight's object list; here the beNDMWStatus. */
int FUN_00236f80(int, int);
PropertyRecord *igProperty_GetRecord(int, char *);
int beNDMWItemBase_GetRecordInt(int, int, char *);

/* The equipment eligibility test: the item at a list index may be equipped when the player's LEVEL
 * property is at least the item's LVPOINT record. */
int Gap__Bec__beNDMWStatusMainSlot__vfunc_30(beNDMWStatusMainSlot *self, int index) {
    int status;
    int item;
    int player_level;

    item = *(int *)(((beNDMWItemBaseList *)self->_deviceFolder)->_data + (index * 4));
    status = FUN_00236f80(self->_insight, g_beNDMWStatus_metaObject[0]);
    player_level = igProperty_GetRecord(self->_playerList, LEVEL_3)->value;
    return player_level >= beNDMWItemBase_GetRecordInt(item, status, LVPOINT);
}
}
