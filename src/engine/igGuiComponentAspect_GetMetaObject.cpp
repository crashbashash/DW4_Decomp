#include "dw4/reflected.h"
extern igMetaObject *g_igGuiComponentAspect_metaObject[4];
extern "C" {
void igGuiComponentAspect_EnsureRegistered(void);
igMetaObject *igGuiComponentAspect_GetMetaObject(void);
}
igMetaObject *igGuiComponentAspect_GetMetaObject(void)
{
    igMetaObject *g = g_igGuiComponentAspect_metaObject[0];
    bool t;
    if (!g || !(t = g->_validity & 4))
        igGuiComponentAspect_EnsureRegistered();
    return g_igGuiComponentAspect_metaObject[0];
}
