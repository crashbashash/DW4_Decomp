#include "dw4/reflected.h"
extern igMetaObject *g_igGeometryAttr_metaObject[4];
extern "C" {
void FUN_001378f0(void);
igMetaObject *igGeometryAttr_GetMetaObject(void);
}
igMetaObject *igGeometryAttr_GetMetaObject(void)
{
    igMetaObject *g = g_igGeometryAttr_metaObject[0];
    bool t;
    if (!g || !(t = g->_validity & 4))
        FUN_001378f0();
    return g_igGeometryAttr_metaObject[0];
}
