#include "dw4/reflected.h"
extern igMetaObject *g_igTextureFunctionAttr_metaObject[4];
extern "C" {
void FUN_00131d80(void);
igMetaObject *igTextureFunctionAttr_GetMetaObject(void);
}
igMetaObject *igTextureFunctionAttr_GetMetaObject(void)
{
    igMetaObject *g = g_igTextureFunctionAttr_metaObject[0];
    bool t;
    if (!g || !(t = g->_validity & 4))
        FUN_00131d80();
    return g_igTextureFunctionAttr_metaObject[0];
}
