#include "dw4/reflected.h"
extern igMetaObject *g_igRenderPackagePool_metaObject[4];
extern "C" {
void FUN_00197a10(void);
igMetaObject *igRenderPackagePool_GetMetaObject(void);
}
igMetaObject *igRenderPackagePool_GetMetaObject(void)
{
    igMetaObject *g = g_igRenderPackagePool_metaObject[0];
    bool t;
    if (!g || !(t = g->_validity & 4))
        FUN_00197a10();
    return g_igRenderPackagePool_metaObject[0];
}
