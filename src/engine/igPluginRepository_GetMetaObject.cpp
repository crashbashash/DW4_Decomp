#include "dw4/reflected.h"
extern igMetaObject *g_igPluginRepository_metaObject[4];
extern "C" {
void FUN_002bca90(void);
igMetaObject *igPluginRepository_GetMetaObject(void);
}
igMetaObject *igPluginRepository_GetMetaObject(void)
{
    igMetaObject *g = g_igPluginRepository_metaObject[0];
    if (!g || ((g->_validity & 4) != 0) == false)
        FUN_002bca90();
    return g_igPluginRepository_metaObject[0];
}
