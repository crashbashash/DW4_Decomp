#include "dw4/reflected.h"
extern igMetaObject *g_igRenderPackageList_metaObject[4];
extern "C" {
void FUN_001978a0(void);
igMetaObject *igRenderPackageList_GetMetaObject(void);
}
igMetaObject *igRenderPackageList_GetMetaObject(void)
{
    igMetaObject *g = g_igRenderPackageList_metaObject[0];
    bool t;
    if (!g || !(t = g->_validity & 4))
        FUN_001978a0();
    return g_igRenderPackageList_metaObject[0];
}
