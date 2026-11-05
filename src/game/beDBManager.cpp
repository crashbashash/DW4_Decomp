#include "dw4/reflected.h"
/* src/game/beDBManager.cpp — the beDBManager methods
 *
 * One translation unit: 1 functions, in retail address order.  Folded
 * from the per-function units by tools/merge_units.py; the matching build
 * splits a function back out with tools/units.py, so `make check` still
 * verifies one function at a time. */
extern "C" {
void FUN_00236c40(int, void *);
void Gap__Bec__beDBManager__vfunc_31(beDBManager *, int);
}

/* 0x003a9760 */
void Gap__Bec__beDBManager__vfunc_31(beDBManager *p0, int p1)
{
    FUN_00236c40(p0->_insight, p0);
}
