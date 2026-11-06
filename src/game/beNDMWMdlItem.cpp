/* src/game/beNDMWMdlItem.c — the beNDMWMdlItem methods
 *
 * One translation unit: 2 functions, in retail address order.  Folded
 * from the per-function units by tools/merge_units.py; the matching build
 * splits a function back out with tools/units.py, so `make check` still
 * verifies one function at a time. */
#include "dw4/reflected.h"
/* The retail unit was C++ with exceptions on (it keeps an exception index record);
 * the code is C, so the whole unit keeps C linkage. */
extern "C" {
extern int g_beNDMWMdlItem_metaObject[4];
extern int g_igViewerSceneInfoManager_metaObject[4];
/* Looks up the insight's object list for the entry whose class metaObject is the
 * second argument (hypothesis: igInsightCore::FindObjectByMetaObject;
 * the matched body is src/unmatched/FUN_00236f80.cpp). */
int FUN_00236f80(int, int);
int Gap__Core__igObject__vfunc_23();

/* slot 23: after the shared igObject slot 23 body, cache the viewer scene-info manager registered
 * with the insight core (_viewerSIManager), found by its class metaObject; the same binding step
 * as the other managers' slot 23. */
void Gap__Bec__beNDMWMdlItem__vfunc_23(beNDMWMdlItem *self) {
    Gap__Core__igObject__vfunc_23();
    self->_viewerSIManager = FUN_00236f80(self->_insight, g_igViewerSceneInfoManager_metaObject[0]);
}

/* 0x00443100 — slot 20: the class's metaObject handle (0x58b4a8). */
int Gap__Bec__beNDMWMdlItem__vfunc_20(void)
{
    return g_beNDMWMdlItem_metaObject[0];
}
} /* extern "C" */
