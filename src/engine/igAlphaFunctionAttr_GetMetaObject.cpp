#include "dw4/reflected.h"
extern igMetaObject *g_igAlphaFunctionAttr_metaObject[4];
extern "C" {
void FUN_0013b560(void);
igMetaObject *igAlphaFunctionAttr_GetMetaObject(void);
}
igMetaObject *igAlphaFunctionAttr_GetMetaObject(void)
{
    igMetaObject *g = g_igAlphaFunctionAttr_metaObject[0];
    if (!g || ((g->_validity & 4) != 0) == false)
        FUN_0013b560();
    return g_igAlphaFunctionAttr_metaObject[0];
}
