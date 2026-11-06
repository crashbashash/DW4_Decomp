#include "dw4/reflected.h"
extern igMetaObject *g_igInfoManager_metaObject[4];
extern "C" {
void FUN_00233910(void);
igMetaObject *igInfoManager_GetMetaObject(void);
}
igMetaObject *igInfoManager_GetMetaObject(void)
{
    igMetaObject *g = g_igInfoManager_metaObject[0];
    bool t;
    if (!g || !(t = g->_validity & 4))
        FUN_00233910();
    return g_igInfoManager_metaObject[0];
}
