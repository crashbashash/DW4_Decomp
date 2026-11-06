#include "dw4/reflected.h"
extern igMetaObject *g_igPluginRepositoryList_metaObject[4];
extern "C" {
void FUN_002bc840(void);
igMetaObject *igPluginRepositoryList_GetMetaObject(void);
}
igMetaObject *igPluginRepositoryList_GetMetaObject(void)
{
    igMetaObject *g = g_igPluginRepositoryList_metaObject[0];
    bool t;
    if (!g || !(t = g->_validity & 4))
        FUN_002bc840();
    return g_igPluginRepositoryList_metaObject[0];
}
