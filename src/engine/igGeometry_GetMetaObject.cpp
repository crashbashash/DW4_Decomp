#include "dw4/reflected.h"
extern igMetaObject *g_igGeometry_metaObject[4];
extern "C" {
void FUN_0019fc00(void);
igMetaObject *igGeometry_GetMetaObject(void);
}
igMetaObject *igGeometry_GetMetaObject(void)
{
    igMetaObject *g = g_igGeometry_metaObject[0];
    bool t;
    if (!g || !(t = g->_validity & 4))
        FUN_0019fc00();
    return g_igGeometry_metaObject[0];
}
