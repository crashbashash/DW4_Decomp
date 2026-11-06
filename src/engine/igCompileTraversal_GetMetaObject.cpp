#include "dw4/reflected.h"
extern igMetaObject *g_igCompileTraversal_metaObject[4];
extern "C" {
void FUN_001a3170(void);
igMetaObject *igCompileTraversal_GetMetaObject(void);
}
igMetaObject *igCompileTraversal_GetMetaObject(void)
{
    igMetaObject *g = g_igCompileTraversal_metaObject[0];
    if (!g || ((g->_validity & 4) != 0) == false)
        FUN_001a3170();
    return g_igCompileTraversal_metaObject[0];
}
