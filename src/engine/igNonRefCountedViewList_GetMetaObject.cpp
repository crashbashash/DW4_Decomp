#include "dw4/reflected.h"
extern igMetaObject *g_igNonRefCountedViewList_metaObject[4];
extern "C" {
void igNonRefCountedViewList_EnsureRegistered(void);
igMetaObject *igNonRefCountedViewList_GetMetaObject(void);
}
igMetaObject *igNonRefCountedViewList_GetMetaObject(void)
{
    igMetaObject *g = g_igNonRefCountedViewList_metaObject[0];
    bool t;
    if (!g || !(t = g->_validity & 4))
        igNonRefCountedViewList_EnsureRegistered();
    return g_igNonRefCountedViewList_metaObject[0];
}
