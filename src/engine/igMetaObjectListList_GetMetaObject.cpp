#include "dw4/reflected.h"
extern igMetaObject *g_igMetaObjectListList_metaObject[4];
extern "C" {
void FUN_002c8d80(void);
igMetaObject *igMetaObjectListList_GetMetaObject(void);
}
igMetaObject *igMetaObjectListList_GetMetaObject(void)
{
    igMetaObject *g = g_igMetaObjectListList_metaObject[0];
    bool t;
    if (!g || !(t = g->_validity & 4))
        FUN_002c8d80();
    return g_igMetaObjectListList_metaObject[0];
}
