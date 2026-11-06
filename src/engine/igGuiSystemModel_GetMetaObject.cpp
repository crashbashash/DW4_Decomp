#include "dw4/reflected.h"
extern igMetaObject *g_igGuiSystemModel_metaObject[4];
extern "C" {
void igGuiSystemModel_RunStaticInit(void);
igMetaObject *igGuiSystemModel_GetMetaObject(void);
}
igMetaObject *igGuiSystemModel_GetMetaObject(void)
{
    igMetaObject *g = g_igGuiSystemModel_metaObject[0];
    bool t;
    if (!g || !(t = g->_validity & 4))
        igGuiSystemModel_RunStaticInit();
    return g_igGuiSystemModel_metaObject[0];
}
