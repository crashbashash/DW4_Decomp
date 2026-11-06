#include "dw4/reflected.h"
extern igMetaObject *g_igMemoryPool_metaObject[4];
extern "C" {
void FUN_002c0540(void);
igMetaObject *igMemoryPool_GetMetaObject(void);
}
igMetaObject *igMemoryPool_GetMetaObject(void)
{
    igMetaObject *g = g_igMemoryPool_metaObject[0];
    bool t;
    if (!g || !(t = g->_validity & 4))
        FUN_002c0540();
    return g_igMemoryPool_metaObject[0];
}
