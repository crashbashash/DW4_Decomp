#include "dw4/reflected.h"
extern "C" {
void FUN_00412600(beNDMWStatusPowerSocket *, int, int, char *);
void Gap__Bec__beNDMWStatusPowerSocket__vfunc_39(beNDMWStatusPowerSocket *, char *, char *, int);
}
extern "C" {
void beNDMWStatus_AssignEquipment(beNDMWStatusPowerSocket *, int, int, int);
void Gap__Bec__beNDMWStatusPowerSocket__vfunc_37(beNDMWStatusPowerSocket *, char *, char *, char *);
}

/* Runs the shared helper FUN_00412600 (the DEVICE row selection step; -1 is its "no row" case)
 * over the power socket's WPU pocket list at the current pocket position, passing the first
 * argument through as the row index. The MainSlot sibling does the same with its APU pocket. The
 * other two arguments are unused. */
void Gap__Bec__beNDMWStatusPowerSocket__vfunc_39(beNDMWStatusPowerSocket *self, char *index, char *unusedArg2, int unusedArg3)
{
    FUN_00412600(self, self->_wpuPocket, self->_pocketPos, index);
}

/* Equipment assignment for the power socket's WPU pocket list: the shared helper
 * beNDMWStatus_AssignEquipment gets the pocket list, the pocket position and the device-folder
 * index chosen in _retCode. The MainSlot sibling does the same with its APU pocket. The three
 * arguments are unused. */
void Gap__Bec__beNDMWStatusPowerSocket__vfunc_37(beNDMWStatusPowerSocket *self, char *unusedArg1, char *unusedArg2, char *unusedArg3)
{
    beNDMWStatus_AssignEquipment(self, self->_wpuPocket, self->_pocketPos, self->_retCode);
}
