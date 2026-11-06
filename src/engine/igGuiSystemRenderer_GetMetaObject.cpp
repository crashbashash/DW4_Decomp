#include "dw4/reflected.h"
extern igMetaObject *g_igGuiSystemRenderer_metaObject[4];
extern "C" {
void igGuiSystemRenderer_RunStaticInit(void);
igMetaObject *igGuiSystemRenderer_GetMetaObject(void);
}
igMetaObject *igGuiSystemRenderer_GetMetaObject(void)
{
    igMetaObject *g = g_igGuiSystemRenderer_metaObject[0];
    if (!g || ((g->_validity & 4) != 0) == false)
        igGuiSystemRenderer_RunStaticInit();
    return g_igGuiSystemRenderer_metaObject[0];
}
