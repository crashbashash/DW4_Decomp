/* src/game/beNDMWAfsSetup.c — the beNDMWAfsSetup methods
 *
 * One translation unit: 6 functions, in retail address order.  Folded
 * from the per-function units by tools/merge_units.py; the matching build
 * splits a function back out with tools/units.py, so `make check` still
 * verifies one function at a time. */
#include "dw4/reflected.h"
/* The retail unit was C++ with exceptions on (it keeps an exception index record);
 * the code is C, so the whole unit keeps C linkage. */
extern "C" {
extern int g_beCri_metaObject_00589ad8[4];
extern int g_beNDMWAfsSetup_metaObject_0058c158[4];
/* Looks up the insight's object list for the entry whose class metaObject is the
 * second argument (hypothesis: igInsightCore::FindObjectByMetaObject; matched body
 * src/unmatched/FUN_00236f80.cpp). */
int FUN_00236f80(int, int);
/* Takes the beCri component but never reads it: the 32-byte body (asm/FUN_0037d2f0.s)
 * only calls FUN_00332e90(-1, 0), the global string/object-list teardown
 * (archived near-miss note wave21). */
int FUN_0037d2f0(int);

/* 0x003cdb00: empty virtual slot 21 */
void Gap__Bec__beNDMWAfsSetup__vfunc_21(void)
{
}

/* 0x003cdb10: empty virtual slot 22 */
void Gap__Bec__beNDMWAfsSetup__vfunc_22(void)
{
}

/* 0x003cdb20: empty virtual slot 23 */
void Gap__Bec__beNDMWAfsSetup__vfunc_23(void)
{
}

/* 0x003cdb30: finds the insight's beCri component (CRI sound middleware owner, handle 0x589ad8)
 * and hands it to FUN_0037d2f0, which tears down the global string/object lists. */
void Gap__Bec__beNDMWAfsSetup__vfunc_24(beNDMWAfsSetup *self) {
    FUN_0037d2f0(FUN_00236f80(self->_insight, g_beCri_metaObject_00589ad8[0]));
}

/* 0x003cdeb0: empty virtual slot 27 */
void Gap__Bec__beNDMWAfsSetup__vfunc_27(void)
{
}

/* 0x003cdee0: class metaObject accessor (RTTI handle at 0x0058c158) */
int Gap__Bec__beNDMWAfsSetup__vfunc_20(void)
{
    return g_beNDMWAfsSetup_metaObject_0058c158[0];
}
} /* extern "C" */
