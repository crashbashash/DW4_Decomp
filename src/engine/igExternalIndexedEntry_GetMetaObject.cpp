#include "dw4/reflected.h"
extern igMetaObject *g_igExternalIndexedEntry_metaObject[4];
extern "C" {
void FUN_002c52d0(void);
igMetaObject *igExternalIndexedEntry_GetMetaObject(void);
}
igMetaObject *igExternalIndexedEntry_GetMetaObject(void)
{
    igMetaObject *g = g_igExternalIndexedEntry_metaObject[0];
    bool t;
    if (!g || !(t = g->_validity & 4))
        FUN_002c52d0();
    return g_igExternalIndexedEntry_metaObject[0];
}
