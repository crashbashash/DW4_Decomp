#include "dw4/reflected.h"
extern igMetaObject *g_igImageUtils_metaObject[4];
extern "C" {
void FUN_0014dcc0(void);
igMetaObject *igImageUtils_GetMetaObject(void);
}
igMetaObject *igImageUtils_GetMetaObject(void)
{
    igMetaObject *g = g_igImageUtils_metaObject[0];
    if (!g || ((g->_validity & 4) != 0) == false)
        FUN_0014dcc0();
    return g_igImageUtils_metaObject[0];
}
