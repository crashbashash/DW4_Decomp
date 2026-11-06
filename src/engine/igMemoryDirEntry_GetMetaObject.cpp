#include "dw4/reflected.h"
extern igMetaObject *g_igMemoryDirEntry_metaObject[4];
extern "C" {
void FUN_002c0ea0(void);
igMetaObject *igMemoryDirEntry_GetMetaObject(void);
}
igMetaObject *igMemoryDirEntry_GetMetaObject(void)
{
    igMetaObject *g = g_igMemoryDirEntry_metaObject[0];
    if (!g || ((g->_validity & 4) != 0) == false)
        FUN_002c0ea0();
    return g_igMemoryDirEntry_metaObject[0];
}
