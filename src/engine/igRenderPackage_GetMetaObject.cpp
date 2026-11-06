#include "dw4/reflected.h"
extern igMetaObject *g_igRenderPackage_metaObject[4];
extern "C" {
void FUN_00197cc0(void);
igMetaObject *igRenderPackage_GetMetaObject(void);
}
igMetaObject *igRenderPackage_GetMetaObject(void)
{
    igMetaObject *g = g_igRenderPackage_metaObject[0];
    bool t;
    if (!g || !(t = g->_validity & 4))
        FUN_00197cc0();
    return g_igRenderPackage_metaObject[0];
}
