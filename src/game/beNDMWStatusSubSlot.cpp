/* src/game/beNDMWStatusSubSlot.cpp — the beNDMWStatusSubSlot methods
 *
 * One translation unit: 2 functions, in retail address order.  Folded
 * from the per-function units by tools/merge_units.py; the matching build
 * splits a function back out with tools/units.py, so `make check` still
 * verifies one function at a time. */
#include "dw4/reflected.h"
extern "C" {
void beNDMWStatus_AssignEquipment(beNDMWStatusSubSlot *, int, int, int);
void Gap__Bec__beNDMWStatusSubSlot__vfunc_31(beNDMWStatusSubSlot *, char *, char *, char *);
}
extern "C" {
void FUN_00412600(beNDMWStatusSubSlot *, int, int, char *);
void Gap__Bec__beNDMWStatusSubSlot__vfunc_32(beNDMWStatusSubSlot *, char *, char *, int);
}

/* 0x00417fc0 - slot 31: equipment assignment for the sub slot.  beNDMWStatus_AssignEquipment
 * (equip by shared item identity, toggle-off, chip-family
 * exclusion) takes the slot list (_subSlot), the entry position in it
 * (_kindListPos) and the index chosen in the device folder (_retCode; the asm
 * bounds-checks it against the list at +120, _deviceFolder).  The PowerSocket
 * and MainSlot siblings have the same body.  The three arguments are unused. */
void Gap__Bec__beNDMWStatusSubSlot__vfunc_31(beNDMWStatusSubSlot *self, char *unusedArg1, char *unusedArg2, char *unusedArg3)
{
    beNDMWStatus_AssignEquipment(self, self->_subSlot, self->_kindListPos, self->_retCode);
}

/* 0x00418000 - slot 32: run the shared helper FUN_00412600 (* the DEVICE row selection step; -1 is its "no row" case per the asm) over
 * the sub slot's list at the current list position, passing the first
 * argument through as the row index.  The other two arguments are unused. */
void Gap__Bec__beNDMWStatusSubSlot__vfunc_32(beNDMWStatusSubSlot *self, char *index, char *unusedArg2, int unusedArg3)
{
    FUN_00412600(self, self->_subSlot, self->_kindListPos, index);
}
