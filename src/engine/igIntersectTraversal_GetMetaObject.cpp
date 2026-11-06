#include "dw4/reflected.h"
extern igMetaObject *g_igIntersectTraversal_metaObject[4];
extern "C" {
void FUN_0019e440(void);
igMetaObject *igIntersectTraversal_GetMetaObject(void);
}
igMetaObject *igIntersectTraversal_GetMetaObject(void)
{
    igMetaObject *g = g_igIntersectTraversal_metaObject[0];
    if (!g || ((g->_validity & 4) != 0) == false)
        FUN_0019e440();
    return g_igIntersectTraversal_metaObject[0];
}
