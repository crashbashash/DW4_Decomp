#include "dw4/reflected.h"
extern igMetaObject *g_igScissorExt_metaObject[4];
extern "C" {
void FUN_0014bd20(void);
igMetaObject *igScissorExt_GetMetaObject(void);
}
igMetaObject *igScissorExt_GetMetaObject(void)
{
    igMetaObject *g = g_igScissorExt_metaObject[0];
    if (!g || ((g->_validity & 4) != 0) == false)
        FUN_0014bd20();
    return g_igScissorExt_metaObject[0];
}
