#include "dw4/reflected.h"
extern igMetaObject *g_igGuiSystem_metaObject[4];
extern "C" {
void igGuiSystem_RunStaticInit(void);
igMetaObject *igGuiSystem_GetMetaObject(void);
}
igMetaObject *igGuiSystem_GetMetaObject(void)
{
    igMetaObject *g = g_igGuiSystem_metaObject[0];
    if (!g || ((g->_validity & 4) != 0) == false)
        igGuiSystem_RunStaticInit();
    return g_igGuiSystem_metaObject[0];
}
