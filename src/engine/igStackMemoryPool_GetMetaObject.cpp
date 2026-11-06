#include "dw4/reflected.h"
extern igMetaObject *g_igStackMemoryPool_metaObject[4];
extern "C" {
void FUN_002ce050(void);
igMetaObject *igStackMemoryPool_GetMetaObject(void);
}
igMetaObject *igStackMemoryPool_GetMetaObject(void)
{
    igMetaObject *g = g_igStackMemoryPool_metaObject[0];
    bool t;
    if (!g || !(t = g->_validity & 4))
        FUN_002ce050();
    return g_igStackMemoryPool_metaObject[0];
}
