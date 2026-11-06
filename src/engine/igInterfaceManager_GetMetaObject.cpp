#include "dw4/reflected.h"
extern igMetaObject *g_igInterfaceManager_metaObject[4];
extern "C" {
void FUN_00145f60(void);
igMetaObject *igInterfaceManager_GetMetaObject(void);
}
igMetaObject *igInterfaceManager_GetMetaObject(void)
{
    igMetaObject *g = g_igInterfaceManager_metaObject[0];
    if (!g || ((g->_validity & 4) != 0) == false)
        FUN_00145f60();
    return g_igInterfaceManager_metaObject[0];
}
