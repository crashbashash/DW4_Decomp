#include "dw4/reflected.h"
extern igMetaObject *g_igLightStateAttrPool_metaObject[4];
extern "C" {
void FUN_0019a650(void);
igMetaObject *igLightStateAttrPool_GetMetaObject(void);
}
igMetaObject *igLightStateAttrPool_GetMetaObject(void)
{
    igMetaObject *g = g_igLightStateAttrPool_metaObject[0];
    if (!g || ((g->_validity & 4) != 0) == false)
        FUN_0019a650();
    return g_igLightStateAttrPool_metaObject[0];
}
