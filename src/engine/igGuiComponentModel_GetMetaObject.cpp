#include "dw4/reflected.h"
extern igMetaObject *g_igGuiComponentModel_metaObject[4];
extern "C" {
void igGuiComponentModel_RunStaticInit(void);
igMetaObject *igGuiComponentModel_GetMetaObject(void);
}
igMetaObject *igGuiComponentModel_GetMetaObject(void)
{
    igMetaObject *g = g_igGuiComponentModel_metaObject[0];
    bool t;
    if (!g || !(t = g->_validity & 4))
        igGuiComponentModel_RunStaticInit();
    return g_igGuiComponentModel_metaObject[0];
}
