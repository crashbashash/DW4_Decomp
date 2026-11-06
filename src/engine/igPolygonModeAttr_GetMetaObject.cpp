#include "dw4/reflected.h"
extern igMetaObject *g_igPolygonModeAttr_metaObject[4];
extern "C" {
void FUN_00134a20(void);
igMetaObject *igPolygonModeAttr_GetMetaObject(void);
}
igMetaObject *igPolygonModeAttr_GetMetaObject(void)
{
    igMetaObject *g = g_igPolygonModeAttr_metaObject[0];
    if (!g || ((g->_validity & 4) != 0) == false)
        FUN_00134a20();
    return g_igPolygonModeAttr_metaObject[0];
}
