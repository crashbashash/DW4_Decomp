#include "dw4/reflected.h"
extern "C" {
void FUN_00236be0(int, char *);
void Gap__Bec__bePadManager__vfunc_21(bePadManager *, int);
}
extern "C" {
void FUN_00236c40(int, char *);
void Gap__Bec__bePadManager__vfunc_22(bePadManager *, int);
}

/* Hands the object to the insight core's helper FUN_00236be0, which asks the scheduler at +12 of
 * the insight object (_insight) whether it already has the object (scheduler slot 26) and, if not,
 * calls scheduler slot 24 with it. Same body as beMessenger slot 21. The second argument is
 * unused. */
void Gap__Bec__bePadManager__vfunc_21(bePadManager *self, int unusedArg)
{
    FUN_00236be0(self->_insight, (char *)self);
}

/* Counterpart of slot 21 through FUN_00236c40, which calls scheduler slot 25 with the object only
 * when scheduler slot 26 reports it present. Same body as beMessenger slot 22. The second argument
 * is unused. */
void Gap__Bec__bePadManager__vfunc_22(bePadManager *self, int unusedArg)
{
    FUN_00236c40(self->_insight, (char *)self);
}
