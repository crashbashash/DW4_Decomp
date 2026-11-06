#include "dw4/reflected.h"
extern igMetaObject *g_igObjectListList_metaObject[4];
extern "C" {
void FUN_002c88f0(void);
igMetaObject *igObjectListList_GetMetaObject(void);
}
igMetaObject *igObjectListList_GetMetaObject(void)
{
    igMetaObject *g = g_igObjectListList_metaObject[0];
    if (!g || ((g->_validity & 4) != 0) == false)
        FUN_002c88f0();
    return g_igObjectListList_metaObject[0];
}
