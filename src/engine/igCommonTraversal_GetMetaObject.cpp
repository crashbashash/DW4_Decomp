#include "dw4/reflected.h"
extern igMetaObject *g_igCommonTraversal_metaObject[4];
extern "C" {
void FUN_001a3dd0(void);
igMetaObject *igCommonTraversal_GetMetaObject(void);
}
igMetaObject *igCommonTraversal_GetMetaObject(void)
{
    igMetaObject *g = g_igCommonTraversal_metaObject[0];
    if (!g || ((g->_validity & 4) != 0) == false)
        FUN_001a3dd0();
    return g_igCommonTraversal_metaObject[0];
}
