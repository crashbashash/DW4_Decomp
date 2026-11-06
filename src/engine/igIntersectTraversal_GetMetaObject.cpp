#include "dw4/reflected.h"
extern igMetaObject *g_igIntersectTraversal_metaObject[4];
extern "C" {
void FUN_0019e440(void);
igMetaObject *igIntersectTraversal_GetMetaObject(void);
}
igMetaObject *igIntersectTraversal_GetMetaObject(void)
{
    igMetaObject *g = g_igIntersectTraversal_metaObject[0];
    bool t;
    if (!g || !(t = g->_validity & 4))
        FUN_0019e440();
    return g_igIntersectTraversal_metaObject[0];
}
