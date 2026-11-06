#include "dw4/reflected.h"
extern igMetaObject *g_igRayIntersectionFunctionList_metaObject[4];
extern "C" {
void FUN_001894f0(void);
igMetaObject *igRayIntersectionFunctionList_GetMetaObject(void);
}
igMetaObject *igRayIntersectionFunctionList_GetMetaObject(void)
{
    igMetaObject *g = g_igRayIntersectionFunctionList_metaObject[0];
    if (!g || ((g->_validity & 4) != 0) == false)
        FUN_001894f0();
    return g_igRayIntersectionFunctionList_metaObject[0];
}
