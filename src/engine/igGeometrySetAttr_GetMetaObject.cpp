#include "dw4/reflected.h"
extern igMetaObject *g_igGeometrySetAttr_metaObject[4];
extern "C" {
void FUN_00136e90(void);
igMetaObject *igGeometrySetAttr_GetMetaObject(void);
}
igMetaObject *igGeometrySetAttr_GetMetaObject(void)
{
    igMetaObject *g = g_igGeometrySetAttr_metaObject[0];
    if (!g || ((g->_validity & 4) != 0) == false)
        FUN_00136e90();
    return g_igGeometrySetAttr_metaObject[0];
}
