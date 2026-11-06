#include "dw4/reflected.h"
extern igMetaObject *g_igVec4ucList_metaObject[4];
extern "C" {
void FUN_00189f10(void);
igMetaObject *igVec4ucList_GetMetaObject(void);
}
igMetaObject *igVec4ucList_GetMetaObject(void)
{
    igMetaObject *g = g_igVec4ucList_metaObject[0];
    if (!g || ((g->_validity & 4) != 0) == false)
        FUN_00189f10();
    return g_igVec4ucList_metaObject[0];
}
