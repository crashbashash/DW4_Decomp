#include "dw4/reflected.h"
extern igMetaObject *g_igSkin_metaObject[4];
extern "C" {
void FUN_00198290(void);
igMetaObject *igSkin_GetMetaObject(void);
}
igMetaObject *igSkin_GetMetaObject(void)
{
    igMetaObject *g = g_igSkin_metaObject[0];
    if (!g || ((g->_validity & 4) != 0) == false)
        FUN_00198290();
    return g_igSkin_metaObject[0];
}
