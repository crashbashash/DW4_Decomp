#include "dw4/reflected.h"
extern igMetaObject *g_igGeometryMaskAttr_metaObject[4];
extern "C" {
void FUN_00137140(void);
igMetaObject *igGeometryMaskAttr_GetMetaObject(void);
}
igMetaObject *igGeometryMaskAttr_GetMetaObject(void)
{
    igMetaObject *g = g_igGeometryMaskAttr_metaObject[0];
    bool t;
    if (!g || !(t = g->_validity & 4))
        FUN_00137140();
    return g_igGeometryMaskAttr_metaObject[0];
}
