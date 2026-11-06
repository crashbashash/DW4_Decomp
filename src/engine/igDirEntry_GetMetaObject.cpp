#include "dw4/reflected.h"
extern igMetaObject *g_igDirEntry_metaObject[4];
extern "C" {
void FUN_002c7900(void);
igMetaObject *igDirEntry_GetMetaObject(void);
}
igMetaObject *igDirEntry_GetMetaObject(void)
{
    igMetaObject *g = g_igDirEntry_metaObject[0];
    if (!g || ((g->_validity & 4) != 0) == false)
        FUN_002c7900();
    return g_igDirEntry_metaObject[0];
}
