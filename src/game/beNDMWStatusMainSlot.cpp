/* beNDMWStatusMainSlot methods (Gap::Bec::beNDMWStatusMainSlot): two slots of
 * the status screen's main slot that forward to the equipment procedures
 * 0x00411950 and 0x00412600 (findings #796/#802: "STATUS equipment
 * 411950/412600") with the current pocket (`_apuPocket`), the cursor position
 * in it (`_pocketPos`) and one more argument.  Functions are in retail address
 * order. */
#include "dw4/reflected.h"
extern "C" {
/* Equipment procedure of the status screen; the last argument is passed through
 * from the vfunc_39 caller (finding #802, DEVICE). */
void FUN_00412600(int slot, int pocket, int pocketPos, char *extra);
void Gap__Bec__beNDMWStatusMainSlot__vfunc_39(beNDMWStatusMainSlot *, char *, char *, int);
}
extern "C" {
/* Equipment assignment of the status screen (finding #796); the last argument is
 * the slot's `_retCode`. */
void beNDMWStatus_AssignEquipment(int slot, int pocket, int pocketPos, int retCode);
void Gap__Bec__beNDMWStatusMainSlot__vfunc_37(beNDMWStatusMainSlot *, char *, char *, char *);
}

/* 0x004165a0: only the first argument is used. */
void Gap__Bec__beNDMWStatusMainSlot__vfunc_39(beNDMWStatusMainSlot * self, char * extra, char * unusedA, int unusedB)
{
    /* matching construct: (int) cast because the callee takes the receiver as an int */
    FUN_00412600((int)self, self->_apuPocket, self->_pocketPos, extra);
}

/* 0x004170c0: all three arguments are unused. */
void Gap__Bec__beNDMWStatusMainSlot__vfunc_37(beNDMWStatusMainSlot * self, char * unusedA, char * unusedB, char * unusedC)
{
    /* matching construct: (int) cast because the callee takes the receiver as an int */
    beNDMWStatus_AssignEquipment((int)self, self->_apuPocket, self->_pocketPos, self->_retCode);
}
