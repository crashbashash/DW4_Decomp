#include "dw4/reflected.h"
extern igMetaObject *g_igAttrStackList_metaObject[4];
extern "C" {
void FUN_001a59e0(void);
igMetaObject *igAttrStackList_GetMetaObject(void);
}
igMetaObject *igAttrStackList_GetMetaObject(void)
{
    igMetaObject *g = g_igAttrStackList_metaObject[0];
    if (!g || ((g->_validity & 4) != 0) == false)
        FUN_001a59e0();
    return g_igAttrStackList_metaObject[0];
}
