#include "dw4/reflected.h"
extern igMetaObject *g_igDisableExt_metaObject[4];
extern "C" {
void FUN_0014f810(void);
igMetaObject *igDisableExt_GetMetaObject(void);
}
igMetaObject *igDisableExt_GetMetaObject(void)
{
    igMetaObject *g = g_igDisableExt_metaObject[0];
    if (!g || ((g->_validity & 4) != 0) == false)
        FUN_0014f810();
    return g_igDisableExt_metaObject[0];
}
