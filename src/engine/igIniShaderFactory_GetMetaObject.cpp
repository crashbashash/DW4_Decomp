#include "dw4/reflected.h"
extern igMetaObject *g_igIniShaderFactory_metaObject[4];
extern "C" {
void FUN_0019efb0(void);
igMetaObject *igIniShaderFactory_GetMetaObject(void);
}
igMetaObject *igIniShaderFactory_GetMetaObject(void)
{
    igMetaObject *g = g_igIniShaderFactory_metaObject[0];
    bool t;
    if (!g || !(t = g->_validity & 4))
        FUN_0019efb0();
    return g_igIniShaderFactory_metaObject[0];
}
