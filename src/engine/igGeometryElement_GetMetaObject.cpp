#include "dw4/reflected.h"
extern igMetaObject *g_igGeometryElement_metaObject[4];
extern "C" {
void igGeometryElement_EnsureRegistered(void);
igMetaObject *igGeometryElement_GetMetaObject(void);
}
igMetaObject *igGeometryElement_GetMetaObject(void)
{
    igMetaObject *g = g_igGeometryElement_metaObject[0];
    if (!g || ((g->_validity & 4) != 0) == false)
        igGeometryElement_EnsureRegistered();
    return g_igGeometryElement_metaObject[0];
}
