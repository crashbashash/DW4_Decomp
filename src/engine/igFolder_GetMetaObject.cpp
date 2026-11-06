#include "dw4/reflected.h"
extern igMetaObject *g_igFolder_metaObject[4];
extern "C" {
void FUN_002c44c0(void);
igMetaObject *igFolder_GetMetaObject(void);
}
igMetaObject *igFolder_GetMetaObject(void)
{
    igMetaObject *g = g_igFolder_metaObject[0];
    bool t;
    if (!g || !(t = g->_validity & 4))
        FUN_002c44c0();
    return g_igFolder_metaObject[0];
}
