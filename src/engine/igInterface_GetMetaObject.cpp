#include "dw4/reflected.h"
extern igMetaObject *g_igInterface_metaObject[4];
extern "C" {
void FUN_00228c60(void);
igMetaObject *igInterface_GetMetaObject(void);
}
igMetaObject *igInterface_GetMetaObject(void)
{
    igMetaObject *g = g_igInterface_metaObject[0];
    if (!g || ((g->_validity & 4) != 0) == false)
        FUN_00228c60();
    return g_igInterface_metaObject[0];
}
