#include "dw4/reflected.h"
extern igMetaObject *g_igSetRenderDestinationAttr_metaObject[4];
extern "C" {
void FUN_00133d20(void);
igMetaObject *igSetRenderDestinationAttr_GetMetaObject(void);
}
igMetaObject *igSetRenderDestinationAttr_GetMetaObject(void)
{
    igMetaObject *g = g_igSetRenderDestinationAttr_metaObject[0];
    bool t;
    if (!g || !(t = g->_validity & 4))
        FUN_00133d20();
    return g_igSetRenderDestinationAttr_metaObject[0];
}
