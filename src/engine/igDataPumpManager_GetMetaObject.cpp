#include "dw4/reflected.h"
extern igMetaObject *g_igDataPumpManager_metaObject[4];
extern "C" {
void FUN_001e5280(void);
igMetaObject *igDataPumpManager_GetMetaObject(void);
}
igMetaObject *igDataPumpManager_GetMetaObject(void)
{
    igMetaObject *g = g_igDataPumpManager_metaObject[0];
    if (!g || ((g->_validity & 4) != 0) == false)
        FUN_001e5280();
    return g_igDataPumpManager_metaObject[0];
}
