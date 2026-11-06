#include "dw4/reflected.h"
extern igMetaObject *g_igPluginHelper_metaObject[4];
extern "C" {
void FUN_002bc5c0(void);
igMetaObject *igPluginHelper_GetMetaObject(void);
}
igMetaObject *igPluginHelper_GetMetaObject(void)
{
    igMetaObject *g = g_igPluginHelper_metaObject[0];
    if (!g || ((g->_validity & 4) != 0) == false)
        FUN_002bc5c0();
    return g_igPluginHelper_metaObject[0];
}
