/* beTargetObj methods (Gap::Bec::beTargetObj): slots 21 and 22 hand the
 * object to the insight core's scheduler and take it out again.  Each calls a
 * helper on igInsightCore (the `_insight` member, with its `_scheduler` at +12
 * in include/dw4/reflected.h) that asks the scheduler's slot 26 (0x68) whether
 * the object is present and then calls slot 24 (0x60, add) or slot 25 (0x64,
 * remove), hypothetical names.  Functions are in
 * retail address order; the slot argument is unused. */
#include "dw4/reflected.h"
extern "C" {
/* Add `object` to the insight scheduler unless it is already there. */
void FUN_00236be0(int insight, char *object);
void Gap__Bec__beTargetObj__vfunc_21(beTargetObj *, int);
}
extern "C" {
/* Remove `object` from the insight scheduler when it is there. */
void FUN_00236c40(int insight, char *object);
void Gap__Bec__beTargetObj__vfunc_22(beTargetObj *, int);
}

/* 0x003a59d0: register the target with the insight scheduler. */
void Gap__Bec__beTargetObj__vfunc_21(beTargetObj * self, int unused)
{
    FUN_00236be0(self->_insight, (char *)self);
}

/* 0x003a59f0: unregister the target from the insight scheduler. */
void Gap__Bec__beTargetObj__vfunc_22(beTargetObj * self, int unused)
{
    FUN_00236c40(self->_insight, (char *)self);
}
