#include "dw4/reflected.h"
extern igMetaObject *g_igShaderFactory_metaObject[4];
extern "C" {
void FUN_001994d0(void);
igMetaObject *igShaderFactory_GetMetaObject(void);
}
igMetaObject *igShaderFactory_GetMetaObject(void)
{
    igMetaObject *g = g_igShaderFactory_metaObject[0];
    bool t;
    if (!g || !(t = g->_validity & 4))
        FUN_001994d0();
    return g_igShaderFactory_metaObject[0];
}
