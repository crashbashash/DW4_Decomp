#include "dw4/reflected.h"
extern igMetaObject *g_igCollisionGroupList_metaObject[4];
extern "C" {
void FUN_00239b20(void);
igMetaObject *igCollisionGroupList_GetMetaObject(void);
}
igMetaObject *igCollisionGroupList_GetMetaObject(void)
{
    igMetaObject *g = g_igCollisionGroupList_metaObject[0];
    if (!g || ((g->_validity & 4) != 0) == false)
        FUN_00239b20();
    return g_igCollisionGroupList_metaObject[0];
}
