/* src/game/beNDMWMdlPlayer2.c — the beNDMWMdlPlayer2 methods
 *
 * One translation unit: 2 functions, in retail address order.  Folded
 * from the per-function units by tools/merge_units.py; the matching build
 * splits a function back out with tools/units.py, so `make check` still
 * verifies one function at a time. */
#include "dw4/reflected.h"
/* The retail unit was C++ with exceptions on (it keeps an exception index record);
 * the code is C, so the whole unit keeps C linkage. */
extern "C" {
extern int g_bePadManager_metaObject[4];
extern int g_beNDMWMdlPlayer2_metaObject[4];
/* Looks up the insight's object list for the entry whose class metaObject is the
 * second argument (hypothesis: igInsightCore::FindObjectByMetaObject, finding #3188;
 * the matched body is src/unmatched/FUN_00236f80.cpp). */
int FUN_00236f80(int, int);
int Gap__Core__igObject__vfunc_23();

/* 0x003d4980 — slot 23: after the shared igObject slot 23 body, cache the
 * pad manager registered with the insight core (_padManager), found by its
 * class metaObject; the same binding step as the other managers' slot 23
 * (docs/engine/typed-game-layer.md). */
void Gap__Bec__beNDMWMdlPlayer2__vfunc_23(beNDMWMdlPlayer2 *self) {
    Gap__Core__igObject__vfunc_23();
    self->_padManager = FUN_00236f80(self->_insight, g_bePadManager_metaObject[0]);
}

/* 0x003d58e0 — slot 20: the class's metaObject handle (0x58b368). */
int Gap__Bec__beNDMWMdlPlayer2__vfunc_20(void)
{
    return g_beNDMWMdlPlayer2_metaObject[0];
}
} /* extern "C" */
