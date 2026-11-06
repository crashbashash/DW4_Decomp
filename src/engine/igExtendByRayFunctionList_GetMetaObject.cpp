#include "dw4/reflected.h"
extern igMetaObject *g_igExtendByRayFunctionList_metaObject[4];
extern "C" {
void FUN_00189390(void);
igMetaObject *igExtendByRayFunctionList_GetMetaObject(void);
}
igMetaObject *igExtendByRayFunctionList_GetMetaObject(void)
{
    igMetaObject *g = g_igExtendByRayFunctionList_metaObject[0];
    bool t;
    if (!g || !(t = g->_validity & 4))
        FUN_00189390();
    return g_igExtendByRayFunctionList_metaObject[0];
}
