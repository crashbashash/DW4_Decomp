#include "dw4/reflected.h"
extern igMetaObject *g_igMetaObjectList_metaObject[4];
extern "C" {
void FUN_002c8f30(void);
igMetaObject *igMetaObjectList_GetMetaObject(void);
}
igMetaObject *igMetaObjectList_GetMetaObject(void)
{
    igMetaObject *g = g_igMetaObjectList_metaObject[0];
    if (!g || ((g->_validity & 4) != 0) == false)
        FUN_002c8f30();
    return g_igMetaObjectList_metaObject[0];
}
