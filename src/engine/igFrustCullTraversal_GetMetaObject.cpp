#include "dw4/reflected.h"
extern igMetaObject *g_igFrustCullTraversal_metaObject[4];
extern "C" {
void FUN_001a1170(void);
igMetaObject *igFrustCullTraversal_GetMetaObject(void);
}
igMetaObject *igFrustCullTraversal_GetMetaObject(void)
{
    igMetaObject *g = g_igFrustCullTraversal_metaObject[0];
    if (!g || ((g->_validity & 4) != 0) == false)
        FUN_001a1170();
    return g_igFrustCullTraversal_metaObject[0];
}
