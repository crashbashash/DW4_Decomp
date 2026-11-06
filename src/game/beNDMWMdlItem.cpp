#include "dw4/reflected.h"
extern "C" {
extern int g_beNDMWMdlItem_metaObject[4];
extern int g_igViewerSceneInfoManager_metaObject[4];
/* Looks up the insight's object list for the entry whose class metaObject is the second argument. */
int FUN_00236f80(int, int);
int Gap__Core__igObject__vfunc_23();

/* After the shared igObject slot 23 body, caches the viewer scene-info manager registered with the
 * insight core (_viewerSIManager), found by its class metaObject; the same binding step as the
 * other managers' slot 23. */
void Gap__Bec__beNDMWMdlItem__vfunc_23(beNDMWMdlItem *self) {
    Gap__Core__igObject__vfunc_23();
    self->_viewerSIManager = FUN_00236f80(self->_insight, g_igViewerSceneInfoManager_metaObject[0]);
}

int Gap__Bec__beNDMWMdlItem__vfunc_20(void)
{
    return g_beNDMWMdlItem_metaObject[0];
}
}
