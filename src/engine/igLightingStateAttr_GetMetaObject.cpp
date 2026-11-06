#include "dw4/reflected.h"
extern igMetaObject *g_igLightingStateAttr_metaObject[4];
extern "C" {
void FUN_00135f40(void);
igMetaObject *igLightingStateAttr_GetMetaObject(void);
}
igMetaObject *igLightingStateAttr_GetMetaObject(void)
{
    igMetaObject *g = g_igLightingStateAttr_metaObject[0];
    if (!g || ((g->_validity & 4) != 0) == false)
        FUN_00135f40();
    return g_igLightingStateAttr_metaObject[0];
}
