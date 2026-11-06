#include "dw4/reflected.h"
extern igMetaObject *g_igGeometrySetAttr_metaObject[4];
extern "C" {
void FUN_00136e90(void);
igMetaObject *igGeometrySetAttr_GetMetaObject(void);
}
igMetaObject *igGeometrySetAttr_GetMetaObject(void)
{
    igMetaObject *g = g_igGeometrySetAttr_metaObject[0];
    bool t;
    if (!g || !(t = g->_validity & 4))
        FUN_00136e90();
    return g_igGeometrySetAttr_metaObject[0];
}
