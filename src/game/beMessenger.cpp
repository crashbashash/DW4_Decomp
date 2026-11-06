#include "dw4/reflected.h"
extern "C" {
void FUN_00236be0(int, char *);
void Gap__Bec__beMessenger__vfunc_21(beMessenger *, int);
}
extern "C" {
void FUN_00236c40(int, char *);
void Gap__Bec__beMessenger__vfunc_22(beMessenger *, int);
}
extern "C" {
void beMessenger_ResetMemory(beMessenger *);
void Gap__Bec__beMessenger__vfunc_26(beMessenger *);
}

/* Hands the messenger to the insight core's helper FUN_00236be0, which asks the core's scheduler
 * (_scheduler, +12) whether it already holds the object (scheduler slot 26) and, if not, calls
 * scheduler slot 24 with it. The second argument is unused. */
void Gap__Bec__beMessenger__vfunc_21(beMessenger *self, int unusedArg)
{
    FUN_00236be0(self->_insight, (char *)self); /* matching construct: char * parameter on FUN_00236*, receiver passed as a byte pointer */
}

/* Counterpart of slot 21 through FUN_00236c40, which calls scheduler slot 25 with the object only
 * when scheduler slot 26 reports it present. The second argument is unused. */
void Gap__Bec__beMessenger__vfunc_22(beMessenger *self, int unusedArg)
{
    FUN_00236c40(self->_insight, (char *)self); /* matching construct: char * parameter on FUN_00236*, receiver passed as a byte pointer */
}

void Gap__Bec__beMessenger__vfunc_26(beMessenger *self)
{
    beMessenger_ResetMemory(self);
}
