#include "dw4/reflected.h"
extern igMetaObject *g_igLightStateAttrPool_metaObject[4];
extern "C" {
void FUN_0019a650(void);
igMetaObject *igLightStateAttrPool_GetMetaObject(void);
}
igMetaObject *igLightStateAttrPool_GetMetaObject(void)
{
    igMetaObject *g = g_igLightStateAttrPool_metaObject[0];
    bool t;
    if (!g || !(t = g->_validity & 4))
        FUN_0019a650();
    return g_igLightStateAttrPool_metaObject[0];
}
