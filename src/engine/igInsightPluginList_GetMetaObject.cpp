#include "dw4/reflected.h"
extern igMetaObject *g_igInsightPluginList_metaObject[4];
extern "C" {
void FUN_002326a0(void);
igMetaObject *igInsightPluginList_GetMetaObject(void);
}
igMetaObject *igInsightPluginList_GetMetaObject(void)
{
    igMetaObject *g = g_igInsightPluginList_metaObject[0];
    bool t;
    if (!g || !(t = g->_validity & 4))
        FUN_002326a0();
    return g_igInsightPluginList_metaObject[0];
}
