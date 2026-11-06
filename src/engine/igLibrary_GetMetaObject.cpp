#include "dw4/reflected.h"
extern igMetaObject *g_igLibrary_metaObject[4];
extern "C" {
void FUN_002c2570(void);
igMetaObject *igLibrary_GetMetaObject(void);
}
igMetaObject *igLibrary_GetMetaObject(void)
{
    igMetaObject *g = g_igLibrary_metaObject[0];
    bool t;
    if (!g || !(t = g->_validity & 4))
        FUN_002c2570();
    return g_igLibrary_metaObject[0];
}
