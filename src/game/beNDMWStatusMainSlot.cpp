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
