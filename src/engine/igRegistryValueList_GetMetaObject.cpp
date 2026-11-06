#include "dw4/reflected.h"
extern igMetaObject *g_igRegistryValueList_metaObject[4];
extern "C" {
void FUN_002bb470(void);
igMetaObject *igRegistryValueList_GetMetaObject(void);
}
igMetaObject *igRegistryValueList_GetMetaObject(void)
{
    igMetaObject *g = g_igRegistryValueList_metaObject[0];
    bool t;
    if (!g || !(t = g->_validity & 4))
        FUN_002bb470();
    return g_igRegistryValueList_metaObject[0];
}
