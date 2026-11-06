#include "dw4/reflected.h"
extern igMetaObject *g_igGeometryElement_metaObject[4];
extern "C" {
void igGeometryElement_EnsureRegistered(void);
igMetaObject *igGeometryElement_GetMetaObject(void);
}
igMetaObject *igGeometryElement_GetMetaObject(void)
{
    igMetaObject *g = g_igGeometryElement_metaObject[0];
    bool t;
    if (!g || !(t = g->_validity & 4))
        igGeometryElement_EnsureRegistered();
    return g_igGeometryElement_metaObject[0];
}
