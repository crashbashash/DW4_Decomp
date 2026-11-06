#include "dw4/reflected.h"
extern igMetaObject *g_igLibraryLoader_metaObject[4];
extern "C" {
void FUN_002c2330(void);
igMetaObject *igLibraryLoader_GetMetaObject(void);
}
igMetaObject *igLibraryLoader_GetMetaObject(void)
{
    igMetaObject *g = g_igLibraryLoader_metaObject[0];
    bool t;
    if (!g || !(t = g->_validity & 4))
        FUN_002c2330();
    return g_igLibraryLoader_metaObject[0];
}
