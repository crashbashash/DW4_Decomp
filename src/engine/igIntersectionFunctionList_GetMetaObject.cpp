#include "dw4/reflected.h"
extern igMetaObject *g_igIntersectionFunctionList_metaObject[4];
extern "C" {
void FUN_00189910(void);
igMetaObject *igIntersectionFunctionList_GetMetaObject(void);
}
igMetaObject *igIntersectionFunctionList_GetMetaObject(void)
{
    igMetaObject *g = g_igIntersectionFunctionList_metaObject[0];
    bool t;
    if (!g || !(t = g->_validity & 4))
        FUN_00189910();
    return g_igIntersectionFunctionList_metaObject[0];
}
