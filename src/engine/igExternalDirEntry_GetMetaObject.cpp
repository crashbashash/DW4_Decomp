#include "dw4/reflected.h"
extern igMetaObject *g_igExternalDirEntry_metaObject[4];
extern "C" {
void FUN_002c5550(void);
igMetaObject *igExternalDirEntry_GetMetaObject(void);
}
igMetaObject *igExternalDirEntry_GetMetaObject(void)
{
    igMetaObject *g = g_igExternalDirEntry_metaObject[0];
    bool t;
    if (!g || !(t = g->_validity & 4))
        FUN_002c5550();
    return g_igExternalDirEntry_metaObject[0];
}
