#include "dw4/reflected.h"
extern igMetaObject *g_igRenderListAttr_metaObject[4];
extern "C" {
void FUN_00133f80(void);
igMetaObject *igRenderListAttr_GetMetaObject(void);
}
igMetaObject *igRenderListAttr_GetMetaObject(void)
{
    igMetaObject *g = g_igRenderListAttr_metaObject[0];
    if (!g || ((g->_validity & 4) != 0) == false)
        FUN_00133f80();
    return g_igRenderListAttr_metaObject[0];
}
