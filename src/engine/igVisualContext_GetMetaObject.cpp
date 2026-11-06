#include "dw4/reflected.h"
extern igMetaObject *g_igVisualContext_metaObject[4];
extern "C" {
void FUN_0014a0e0(void);
igMetaObject *igVisualContext_GetMetaObject(void);
}
igMetaObject *igVisualContext_GetMetaObject(void)
{
    igMetaObject *g = g_igVisualContext_metaObject[0];
    if (!g || ((g->_validity & 4) != 0) == false)
        FUN_0014a0e0();
    return g_igVisualContext_metaObject[0];
}
