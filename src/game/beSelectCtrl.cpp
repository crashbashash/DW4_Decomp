#include "dw4/reflected.h"
extern "C" {
extern int g_beSelectCtrlInfo_metaObject[4];
extern int g_beSelectCtrl_metaObject[4];
int FUN_00236f80(int insight, int metaObject);
extern int D_00588518[];
}

/* raw136 lazily resolves a borrowed pad-manager pointer. No reference-count increment/decrement is
 * present in this body. */
extern "C" {
void beSelectCtrl_EnsurePadManager(beSelectCtrl *self);
int Gap__Bec__beSelectCtrl__vfunc_30(void);
int Gap__Bec__beSelectCtrl__vfunc_20(void);
}
void beSelectCtrl_EnsurePadManager(beSelectCtrl *self)
{
    if (self->_padManager == 0) {
        self->_padManager = FUN_00236f80(self->_insight, D_00588518[0]);
    }
}

int Gap__Bec__beSelectCtrl__vfunc_30(void)
{
    return g_beSelectCtrlInfo_metaObject[0];
}

int Gap__Bec__beSelectCtrl__vfunc_20(void)
{
    return g_beSelectCtrl_metaObject[0];
}
