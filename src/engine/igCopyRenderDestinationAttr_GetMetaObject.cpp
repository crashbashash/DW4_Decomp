#include "dw4/reflected.h"
extern igMetaObject *g_igCopyRenderDestinationAttr_metaObject[4];
extern "C" {
void FUN_00138b20(void);
igMetaObject *igCopyRenderDestinationAttr_GetMetaObject(void);
}
igMetaObject *igCopyRenderDestinationAttr_GetMetaObject(void)
{
    igMetaObject *g = g_igCopyRenderDestinationAttr_metaObject[0];
    bool t;
    if (!g || !(t = g->_validity & 4))
        FUN_00138b20();
    return g_igCopyRenderDestinationAttr_metaObject[0];
}
