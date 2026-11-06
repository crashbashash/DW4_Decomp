#include "dw4/reflected.h"
extern igMetaObject *g_igCapabilityManager_metaObject[4];
extern "C" {
void FUN_0014fde0(void);
igMetaObject *igCapabilityManager_GetMetaObject(void);
}
igMetaObject *igCapabilityManager_GetMetaObject(void)
{
    igMetaObject *g = g_igCapabilityManager_metaObject[0];
    if (!g || ((g->_validity & 4) != 0) == false)
        FUN_0014fde0();
    return g_igCapabilityManager_metaObject[0];
}
