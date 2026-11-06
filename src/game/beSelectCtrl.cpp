/* src/game/beSelectCtrl.cpp — the beSelectCtrl methods
 *
 * One translation unit: 3 functions, in retail address order.  Folded
 * from the per-function units by tools/merge_units.py; the matching build
 * splits a function back out with tools/units.py, so `make check` still
 * verifies one function at a time. */

#include "dw4/reflected.h"
extern "C" {
extern int g_beSelectCtrlInfo_metaObject[4];
extern int g_beSelectCtrl_metaObject[4];
int FUN_00236f80(int insight, int metaObject);
extern int D_00588518[];
}

/* raw136 lazily resolves a borrowed pad-manager pointer. No reference-count increment/decrement is
 * present in this body. One explicit original padding NOP follows the publication (
 * convention). */
extern "C" {
void beSelectCtrl_EnsurePadManager(beSelectCtrl *self);
int Gap__Bec__beSelectCtrl__vfunc_30(void);
int Gap__Bec__beSelectCtrl__vfunc_20(void);
}
void beSelectCtrl_EnsurePadManager(beSelectCtrl *self)
{
    if (self->_padManager == 0) {
        self->_padManager = FUN_00236f80(self->_insight, D_00588518[0]);
        asm { nop }
    }
}

/* 0x0039cbb0 */
int Gap__Bec__beSelectCtrl__vfunc_30(void)
{
    return g_beSelectCtrlInfo_metaObject[0];
}

/* 0x0039ded0 */
int Gap__Bec__beSelectCtrl__vfunc_20(void)
{
    return g_beSelectCtrl_metaObject[0];
}
