#include "dw4/reflected.h"
extern igMetaObject *g_igTraversal_metaObject[4];
extern "C" {
void FUN_00194530(void);
igMetaObject *igTraversal_GetMetaObject(void);
}
igMetaObject *igTraversal_GetMetaObject(void)
{
    igMetaObject *g = g_igTraversal_metaObject[0];
    if (!g || ((g->_validity & 4) != 0) == false)
        FUN_00194530();
    return g_igTraversal_metaObject[0];
}
