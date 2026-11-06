#include "dw4/reflected.h"
extern igMetaObject *g_igDefaultAspectElementList_metaObject[4];
extern "C" {
void igDefaultAspectElementList_EnsureRegistered(void);
igMetaObject *igDefaultAspectElementList_GetMetaObject(void);
}
igMetaObject *igDefaultAspectElementList_GetMetaObject(void)
{
    igMetaObject *g = g_igDefaultAspectElementList_metaObject[0];
    if (!g || ((g->_validity & 4) != 0) == false)
        igDefaultAspectElementList_EnsureRegistered();
    return g_igDefaultAspectElementList_metaObject[0];
}
