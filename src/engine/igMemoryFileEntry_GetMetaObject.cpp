#include "dw4/reflected.h"
extern igMetaObject *g_igMemoryFileEntry_metaObject[4];
extern "C" {
void FUN_002c0c80(void);
igMetaObject *igMemoryFileEntry_GetMetaObject(void);
}
igMetaObject *igMemoryFileEntry_GetMetaObject(void)
{
    igMetaObject *g = g_igMemoryFileEntry_metaObject[0];
    if (!g || ((g->_validity & 4) != 0) == false)
        FUN_002c0c80();
    return g_igMemoryFileEntry_metaObject[0];
}
