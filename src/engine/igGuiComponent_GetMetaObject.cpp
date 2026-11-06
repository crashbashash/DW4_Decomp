#include "dw4/reflected.h"
extern igMetaObject *g_igGuiComponent_metaObject[4];
extern "C" {
void igGuiComponent_EnsureRegistered(void);
igMetaObject *igGuiComponent_GetMetaObject(void);
}
igMetaObject *igGuiComponent_GetMetaObject(void)
{
    igMetaObject *g = g_igGuiComponent_metaObject[0];
    if (!g || ((g->_validity & 4) != 0) == false)
        igGuiComponent_EnsureRegistered();
    return g_igGuiComponent_metaObject[0];
}
