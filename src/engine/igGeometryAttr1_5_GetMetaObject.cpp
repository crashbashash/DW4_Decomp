#include "dw4/reflected.h"
extern igMetaObject *g_igGeometryAttr1_5_metaObject[4];
extern "C" {
void FUN_001376d0(void);
igMetaObject *igGeometryAttr1_5_GetMetaObject(void);
}
igMetaObject *igGeometryAttr1_5_GetMetaObject(void)
{
    igMetaObject *g = g_igGeometryAttr1_5_metaObject[0];
    if (!g || ((g->_validity & 4) != 0) == false)
        FUN_001376d0();
    return g_igGeometryAttr1_5_metaObject[0];
}
