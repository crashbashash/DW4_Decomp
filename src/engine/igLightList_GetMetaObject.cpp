#include "dw4/reflected.h"
extern igMetaObject *g_igLightList_metaObject[4];
extern "C" {
void FUN_001366c0(void);
igMetaObject *igLightList_GetMetaObject(void);
}
igMetaObject *igLightList_GetMetaObject(void)
{
    igMetaObject *g = g_igLightList_metaObject[0];
    bool t;
    if (!g || !(t = g->_validity & 4))
        FUN_001366c0();
    return g_igLightList_metaObject[0];
}
