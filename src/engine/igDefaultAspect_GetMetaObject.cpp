#include "dw4/reflected.h"
extern igMetaObject *g_igDefaultAspect_metaObject[4];
extern "C" {
void igDefaultAspect_EnsureRegistered(void);
igMetaObject *igDefaultAspect_GetMetaObject(void);
}
igMetaObject *igDefaultAspect_GetMetaObject(void)
{
    igMetaObject *g = g_igDefaultAspect_metaObject[0];
    if (!g || ((g->_validity & 4) != 0) == false)
        igDefaultAspect_EnsureRegistered();
    return g_igDefaultAspect_metaObject[0];
}
