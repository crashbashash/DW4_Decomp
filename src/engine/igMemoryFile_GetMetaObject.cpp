#include "dw4/reflected.h"
extern igMetaObject *g_igMemoryFile_metaObject[4];
extern "C" {
void FUN_002c0890(void);
igMetaObject *igMemoryFile_GetMetaObject(void);
}
igMetaObject *igMemoryFile_GetMetaObject(void)
{
    igMetaObject *g = g_igMemoryFile_metaObject[0];
    bool t;
    if (!g || !(t = g->_validity & 4))
        FUN_002c0890();
    return g_igMemoryFile_metaObject[0];
}
