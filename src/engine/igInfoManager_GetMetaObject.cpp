#include "dw4/reflected.h"
extern igMetaObject *g_igInfoManager_metaObject[4];
extern "C" {
void FUN_00233910(void);
igMetaObject *igInfoManager_GetMetaObject(void);
}
igMetaObject *igInfoManager_GetMetaObject(void)
{
    igMetaObject *g = g_igInfoManager_metaObject[0];
    if (!g || ((g->_validity & 4) != 0) == false)
        FUN_00233910();
    return g_igInfoManager_metaObject[0];
}
