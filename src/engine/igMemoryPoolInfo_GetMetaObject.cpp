#include "dw4/reflected.h"
extern igMetaObject *g_igMemoryPoolInfo_metaObject[4];
extern "C" {
void FUN_002c00f0(void);
igMetaObject *igMemoryPoolInfo_GetMetaObject(void);
}
igMetaObject *igMemoryPoolInfo_GetMetaObject(void)
{
    igMetaObject *g = g_igMemoryPoolInfo_metaObject[0];
    bool t;
    if (!g || !(t = g->_validity & 4))
        FUN_002c00f0();
    return g_igMemoryPoolInfo_metaObject[0];
}
