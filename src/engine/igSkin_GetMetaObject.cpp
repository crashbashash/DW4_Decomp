#include "dw4/reflected.h"
extern igMetaObject *g_igSkin_metaObject[4];
extern "C" {
void FUN_00198290(void);
igMetaObject *igSkin_GetMetaObject(void);
}
igMetaObject *igSkin_GetMetaObject(void)
{
    igMetaObject *g = g_igSkin_metaObject[0];
    bool t;
    if (!g || !(t = g->_validity & 4))
        FUN_00198290();
    return g_igSkin_metaObject[0];
}
