#include "dw4/reflected.h"
extern igMetaObject *g_igVisualContextCapabilityManager_metaObject[4];
extern "C" {
void FUN_00149d50(void);
igMetaObject *igVisualContextCapabilityManager_GetMetaObject(void);
}
igMetaObject *igVisualContextCapabilityManager_GetMetaObject(void)
{
    igMetaObject *g = g_igVisualContextCapabilityManager_metaObject[0];
    bool t;
    if (!g || !(t = g->_validity & 4))
        FUN_00149d50();
    return g_igVisualContextCapabilityManager_metaObject[0];
}
