#include "dw4/reflected.h"
extern igMetaObject *g_igControllerList_metaObject[4];
extern "C" {
void FUN_001463e0(void);
igMetaObject *igControllerList_GetMetaObject(void);
}
igMetaObject *igControllerList_GetMetaObject(void)
{
    igMetaObject *g = g_igControllerList_metaObject[0];
    bool t;
    if (!g || !(t = g->_validity & 4))
        FUN_001463e0();
    return g_igControllerList_metaObject[0];
}
