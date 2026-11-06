#include "dw4/reflected.h"
extern igMetaObject *g_igGuiComponentList_metaObject[4];
extern "C" {
void igGuiComponentList_EnsureRegistered(void);
igMetaObject *igGuiComponentList_GetMetaObject(void);
}
igMetaObject *igGuiComponentList_GetMetaObject(void)
{
    igMetaObject *g = g_igGuiComponentList_metaObject[0];
    bool t;
    if (!g || !(t = g->_validity & 4))
        igGuiComponentList_EnsureRegistered();
    return g_igGuiComponentList_metaObject[0];
}
