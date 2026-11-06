#include "dw4/reflected.h"
extern igMetaObject *g_igTraversal_metaObject[4];
extern "C" {
void FUN_00194530(void);
igMetaObject *igTraversal_GetMetaObject(void);
}
igMetaObject *igTraversal_GetMetaObject(void)
{
    igMetaObject *g = g_igTraversal_metaObject[0];
    bool t;
    if (!g || !(t = g->_validity & 4))
        FUN_00194530();
    return g_igTraversal_metaObject[0];
}
