#include "dw4/reflected.h"
extern igMetaObject *g_igGenericCapabilityManager_metaObject[4];
extern "C" {
void FUN_0014f390(void);
igMetaObject *igGenericCapabilityManager_GetMetaObject(void);
}
igMetaObject *igGenericCapabilityManager_GetMetaObject(void)
{
    igMetaObject *g = g_igGenericCapabilityManager_metaObject[0];
    bool t;
    if (!g || !(t = g->_validity & 4))
        FUN_0014f390();
    return g_igGenericCapabilityManager_metaObject[0];
}
