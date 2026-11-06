#include "dw4/reflected.h"
extern igMetaObject *g_igScissorExt_metaObject[4];
extern "C" {
void FUN_0014bd20(void);
igMetaObject *igScissorExt_GetMetaObject(void);
}
igMetaObject *igScissorExt_GetMetaObject(void)
{
    igMetaObject *g = g_igScissorExt_metaObject[0];
    bool t;
    if (!g || !(t = g->_validity & 4))
        FUN_0014bd20();
    return g_igScissorExt_metaObject[0];
}
