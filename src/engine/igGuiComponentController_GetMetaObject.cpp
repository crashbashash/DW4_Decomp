#include "dw4/reflected.h"
extern igMetaObject *g_igGuiComponentController_metaObject[4];
extern "C" {
void igGuiComponentController_EnsureRegistered(void);
igMetaObject *igGuiComponentController_GetMetaObject(void);
}
igMetaObject *igGuiComponentController_GetMetaObject(void)
{
    igMetaObject *g = g_igGuiComponentController_metaObject[0];
    bool t;
    if (!g || !(t = g->_validity & 4))
        igGuiComponentController_EnsureRegistered();
    return g_igGuiComponentController_metaObject[0];
}
