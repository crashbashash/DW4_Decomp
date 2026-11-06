#include "dw4/reflected.h"
extern igMetaObject *g_igObjectDirEntry_metaObject[4];
extern "C" {
void FUN_002bda10(void);
igMetaObject *igObjectDirEntry_GetMetaObject(void);
}
igMetaObject *igObjectDirEntry_GetMetaObject(void)
{
    igMetaObject *g = g_igObjectDirEntry_metaObject[0];
    if (!g || ((g->_validity & 4) != 0) == false)
        FUN_002bda10();
    return g_igObjectDirEntry_metaObject[0];
}
