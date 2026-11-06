#include "dw4/reflected.h"
extern igMetaObject *g_igShaderFactoryList_metaObject[4];
extern "C" {
void FUN_00199080(void);
igMetaObject *igShaderFactoryList_GetMetaObject(void);
}
igMetaObject *igShaderFactoryList_GetMetaObject(void)
{
    igMetaObject *g = g_igShaderFactoryList_metaObject[0];
    bool t;
    if (!g || !(t = g->_validity & 4))
        FUN_00199080();
    return g_igShaderFactoryList_metaObject[0];
}
