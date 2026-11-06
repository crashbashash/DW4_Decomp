/* src/game/beFileListInfoManager.cpp — the beFileListInfoManager methods
 *
 * One translation unit: 2 functions, in retail address order.  Folded
 * from the per-function units by tools/merge_units.py; the matching build
 * splits a function back out with tools/units.py, so `make check` still
 * verifies one function at a time. */
#include "dw4/reflected.h"
extern "C" {
void FUN_00236be0(int, beFileListInfoManager *);
void Gap__Bec__beFileListInfoManager__vfunc_21(beFileListInfoManager *, int);
}
extern "C" {
void FUN_00236c40(int, beFileListInfoManager *);
void Gap__Bec__beFileListInfoManager__vfunc_22(beFileListInfoManager *, int);
}

/* slot 21: hand the object to the insight core's helper FUN_00236be0, which (asm) asks the
 * scheduler at +12 of the insight object it is given (_insight) whether it already has the object
 * (scheduler slot 26) and, if not, calls scheduler slot 24 with it. Same body as beMessenger slot
 * 21. The second argument is unused. */
void Gap__Bec__beFileListInfoManager__vfunc_21(beFileListInfoManager *self, int unusedArg)
{
    FUN_00236be0(self->_insight, self);
}

/* 0x0037f240 - slot 22: the counterpart of slot 21 through FUN_00236c40, which calls
 * scheduler slot 25 with the object only when scheduler slot 26 reports it
 * present.  Same body as beMessenger slot 22.  The second argument is unused. */
void Gap__Bec__beFileListInfoManager__vfunc_22(beFileListInfoManager *self, int unusedArg)
{
    FUN_00236c40(self->_insight, self);
}
