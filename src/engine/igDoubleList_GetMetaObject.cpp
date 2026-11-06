#include "dw4/reflected.h"
extern igMetaObject *g_igDoubleList_metaObject[4];
extern "C" {
void FUN_002c9480(void);
igMetaObject *igDoubleList_GetMetaObject(void);
}
igMetaObject *igDoubleList_GetMetaObject(void)
{
    igMetaObject *g = g_igDoubleList_metaObject[0];
    if (!g || ((g->_validity & 4) != 0) == false)
        FUN_002c9480();
    return g_igDoubleList_metaObject[0];
}
