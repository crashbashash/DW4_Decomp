#include "dw4/reflected.h"
extern igMetaObject *g_igDefaultAspectElement_metaObject[4];
extern "C" {
void igDefaultAspectElement_EnsureRegistered(void);
igMetaObject *igDefaultAspectElement_GetMetaObject(void);
}
igMetaObject *igDefaultAspectElement_GetMetaObject(void)
{
    igMetaObject *g = g_igDefaultAspectElement_metaObject[0];
    if (!g || ((g->_validity & 4) != 0) == false)
        igDefaultAspectElement_EnsureRegistered();
    return g_igDefaultAspectElement_metaObject[0];
}
