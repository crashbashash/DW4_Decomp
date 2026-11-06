#include "dw4/reflected.h"
extern igMetaObject *g_igIntListList_metaObject[4];
extern "C" {
void FUN_002c8a60(void);
igMetaObject *igIntListList_GetMetaObject(void);
}
igMetaObject *igIntListList_GetMetaObject(void)
{
    igMetaObject *g = g_igIntListList_metaObject[0];
    if (!g || ((g->_validity & 4) != 0) == false)
        FUN_002c8a60();
    return g_igIntListList_metaObject[0];
}
