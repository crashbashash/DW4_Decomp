#include "dw4/reflected.h"
extern igMetaObject *g_igLightStateSet_metaObject[4];
extern "C" {
void FUN_0019da60(void);
igMetaObject *igLightStateSet_GetMetaObject(void);
}
igMetaObject *igLightStateSet_GetMetaObject(void)
{
    igMetaObject *g = g_igLightStateSet_metaObject[0];
    if (!g || ((g->_validity & 4) != 0) == false)
        FUN_0019da60();
    return g_igLightStateSet_metaObject[0];
}
