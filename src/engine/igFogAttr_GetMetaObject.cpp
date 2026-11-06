#include "dw4/reflected.h"
extern igMetaObject *g_igFogAttr_metaObject[4];
extern "C" {
void FUN_00137e30(void);
igMetaObject *igFogAttr_GetMetaObject(void);
}
igMetaObject *igFogAttr_GetMetaObject(void)
{
    igMetaObject *g = g_igFogAttr_metaObject[0];
    bool t;
    if (!g || !(t = g->_validity & 4))
        FUN_00137e30();
    return g_igFogAttr_metaObject[0];
}
