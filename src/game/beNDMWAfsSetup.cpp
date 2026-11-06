#include "dw4/reflected.h"
extern "C" {
extern int g_beCri_metaObject[4];
extern int g_beNDMWAfsSetup_metaObject[4];
/* Looks up the insight's object list for the entry whose class metaObject is the second argument. */
int FUN_00236f80(int, int);
/* Takes the beCri component but never reads it: the body only calls FUN_00332e90(-1, 0), the
 * global string/object-list teardown. */
int FUN_0037d2f0(int);

/* Empty virtual slot 21 */
void Gap__Bec__beNDMWAfsSetup__vfunc_21(void)
{
}

/* Empty virtual slot 22 */
void Gap__Bec__beNDMWAfsSetup__vfunc_22(void)
{
}

/* Empty virtual slot 23 */
void Gap__Bec__beNDMWAfsSetup__vfunc_23(void)
{
}

/* Finds the insight's beCri component (CRI sound middleware owner) and hands it to FUN_0037d2f0,
 * which tears down the global string/object lists. */
void Gap__Bec__beNDMWAfsSetup__vfunc_24(beNDMWAfsSetup *self) {
    FUN_0037d2f0(FUN_00236f80(self->_insight, g_beCri_metaObject[0]));
}

/* Empty virtual slot 27 */
void Gap__Bec__beNDMWAfsSetup__vfunc_27(void)
{
}

int Gap__Bec__beNDMWAfsSetup__vfunc_20(void)
{
    return g_beNDMWAfsSetup_metaObject[0];
}
}
