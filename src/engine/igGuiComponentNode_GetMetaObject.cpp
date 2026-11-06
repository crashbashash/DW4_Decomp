#include "dw4/reflected.h"
extern igMetaObject *g_igGuiComponentNode_metaObject[4];
extern "C" {
void igGuiComponentNode_RunStaticInit(void);
igMetaObject *igGuiComponentNode_GetMetaObject(void);
}
igMetaObject *igGuiComponentNode_GetMetaObject(void)
{
    igMetaObject *g = g_igGuiComponentNode_metaObject[0];
    bool t;
    if (!g || !(t = g->_validity & 4))
        igGuiComponentNode_RunStaticInit();
    return g_igGuiComponentNode_metaObject[0];
}
