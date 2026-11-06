#include "dw4/reflected.h"
extern igMetaObject *g_igLightStateAttr_metaObject[4];
extern "C" {
void FUN_00136470(void);
igMetaObject *igLightStateAttr_GetMetaObject(void);
}
igMetaObject *igLightStateAttr_GetMetaObject(void)
{
    igMetaObject *g = g_igLightStateAttr_metaObject[0];
    if (!g || ((g->_validity & 4) != 0) == false)
        FUN_00136470();
    return g_igLightStateAttr_metaObject[0];
}
