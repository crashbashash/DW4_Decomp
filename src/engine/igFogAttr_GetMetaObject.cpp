#include "dw4/reflected.h"
extern igMetaObject *g_igFogAttr_metaObject[4];
extern "C" {
void FUN_00137e30(void);
igMetaObject *igFogAttr_GetMetaObject(void);
}
igMetaObject *igFogAttr_GetMetaObject(void)
{
    igMetaObject *g = g_igFogAttr_metaObject[0];
    if (!g || ((g->_validity & 4) != 0) == false)
        FUN_00137e30();
    return g_igFogAttr_metaObject[0];
}
