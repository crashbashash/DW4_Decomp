#include "dw4/reflected.h"
extern igMetaObject *g_igRenderDestinationAttr_metaObject[4];
extern "C" {
void FUN_00134370(void);
igMetaObject *igRenderDestinationAttr_GetMetaObject(void);
}
igMetaObject *igRenderDestinationAttr_GetMetaObject(void)
{
    igMetaObject *g = g_igRenderDestinationAttr_metaObject[0];
    if (!g || ((g->_validity & 4) != 0) == false)
        FUN_00134370();
    return g_igRenderDestinationAttr_metaObject[0];
}
