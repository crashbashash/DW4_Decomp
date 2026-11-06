#include "dw4/reflected.h"
extern igMetaObject *g_igObjectPool_metaObject[4];
extern "C" {
void FUN_001967c0(void);
igMetaObject *igObjectPool_GetMetaObject(void);
}
igMetaObject *igObjectPool_GetMetaObject(void)
{
    igMetaObject *g = g_igObjectPool_metaObject[0];
    bool t;
    if (!g || !(t = g->_validity & 4))
        FUN_001967c0();
    return g_igObjectPool_metaObject[0];
}
