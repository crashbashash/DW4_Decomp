#include "dw4/reflected.h"
extern igMetaObject *g_igStencilFunctionAttr_metaObject[4];
extern "C" {
void FUN_001336e0(void);
igMetaObject *igStencilFunctionAttr_GetMetaObject(void);
}
igMetaObject *igStencilFunctionAttr_GetMetaObject(void)
{
    igMetaObject *g = g_igStencilFunctionAttr_metaObject[0];
    if (!g || ((g->_validity & 4) != 0) == false)
        FUN_001336e0();
    return g_igStencilFunctionAttr_metaObject[0];
}
