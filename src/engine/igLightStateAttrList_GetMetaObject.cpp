#include "dw4/reflected.h"
extern igMetaObject *g_igLightStateAttrList_metaObject[4];
extern "C" {
void FUN_00136120(void);
igMetaObject *igLightStateAttrList_GetMetaObject(void);
}
igMetaObject *igLightStateAttrList_GetMetaObject(void)
{
    igMetaObject *g = g_igLightStateAttrList_metaObject[0];
    bool t;
    if (!g || !(t = g->_validity & 4))
        FUN_00136120();
    return g_igLightStateAttrList_metaObject[0];
}
