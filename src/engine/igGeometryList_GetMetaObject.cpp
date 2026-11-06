#include "dw4/reflected.h"
extern igMetaObject *g_igGeometryList_metaObject[4];
extern "C" {
void FUN_0019fa10(void);
igMetaObject *igGeometryList_GetMetaObject(void);
}
igMetaObject *igGeometryList_GetMetaObject(void)
{
    igMetaObject *g = g_igGeometryList_metaObject[0];
    bool t;
    if (!g || !(t = g->_validity & 4))
        FUN_0019fa10();
    return g_igGeometryList_metaObject[0];
}
