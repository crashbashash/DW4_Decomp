#include "dw4/reflected.h"
extern igMetaObject *g_igControllerManager_metaObject[4];
extern "C" {
void FUN_00146700(void);
igMetaObject *igControllerManager_GetMetaObject(void);
}
igMetaObject *igControllerManager_GetMetaObject(void)
{
    igMetaObject *g = g_igControllerManager_metaObject[0];
    bool t;
    if (!g || !(t = g->_validity & 4))
        FUN_00146700();
    return g_igControllerManager_metaObject[0];
}
