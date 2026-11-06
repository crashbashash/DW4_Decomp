#include "dw4/reflected.h"
extern igMetaObject *g_igGuiComponentAspect_metaObject[4];
extern "C" {
void igGuiComponentAspect_EnsureRegistered(void);
igMetaObject *igGuiComponentAspect_GetMetaObject(void);
}
igMetaObject *igGuiComponentAspect_GetMetaObject(void)
{
    igMetaObject *g = g_igGuiComponentAspect_metaObject[0];
    if (!g || ((g->_validity & 4) != 0) == false)
        igGuiComponentAspect_EnsureRegistered();
    return g_igGuiComponentAspect_metaObject[0];
}
