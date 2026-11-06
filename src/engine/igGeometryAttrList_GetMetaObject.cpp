#include "dw4/reflected.h"
extern igMetaObject *g_igGeometryAttrList_metaObject[4];
extern "C" {
void FUN_0013a5b0(void);
igMetaObject *igGeometryAttrList_GetMetaObject(void);
}
igMetaObject *igGeometryAttrList_GetMetaObject(void)
{
    igMetaObject *g = g_igGeometryAttrList_metaObject[0];
    if (!g || ((g->_validity & 4) != 0) == false)
        FUN_0013a5b0();
    return g_igGeometryAttrList_metaObject[0];
}
