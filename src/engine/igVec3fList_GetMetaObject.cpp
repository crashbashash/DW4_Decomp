#include "dw4/reflected.h"
extern igMetaObject *g_igVec3fList_metaObject[4];
extern "C" {
void FUN_0018a180(void);
igMetaObject *igVec3fList_GetMetaObject(void);
}
igMetaObject *igVec3fList_GetMetaObject(void)
{
    igMetaObject *g = g_igVec3fList_metaObject[0];
    bool t;
    if (!g || !(t = g->_validity & 4))
        FUN_0018a180();
    return g_igVec3fList_metaObject[0];
}
