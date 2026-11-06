#include "dw4/reflected.h"
extern igMetaObject *g_igBlendFunctionAttr_metaObject[4];
extern "C" {
void FUN_0013a040(void);
igMetaObject *igBlendFunctionAttr_GetMetaObject(void);
}
igMetaObject *igBlendFunctionAttr_GetMetaObject(void)
{
    igMetaObject *g = g_igBlendFunctionAttr_metaObject[0];
    if (!g || ((g->_validity & 4) != 0) == false)
        FUN_0013a040();
    return g_igBlendFunctionAttr_metaObject[0];
}
