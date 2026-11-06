#include "dw4/reflected.h"
extern igMetaObject *g_igLightStateAttrList_metaObject[4];
extern "C" {
void FUN_00136120(void);
igMetaObject *igLightStateAttrList_GetMetaObject(void);
}
igMetaObject *igLightStateAttrList_GetMetaObject(void)
{
    igMetaObject *g = g_igLightStateAttrList_metaObject[0];
    if (!g || ((g->_validity & 4) != 0) == false)
        FUN_00136120();
    return g_igLightStateAttrList_metaObject[0];
}
