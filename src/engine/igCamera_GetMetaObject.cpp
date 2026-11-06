#include "dw4/reflected.h"
extern igMetaObject *g_igCamera_metaObject[4];
extern "C" {
void FUN_001a4670(void);
igMetaObject *igCamera_GetMetaObject(void);
}
igMetaObject *igCamera_GetMetaObject(void)
{
    igMetaObject *g = g_igCamera_metaObject[0];
    bool t;
    if (!g || !(t = g->_validity & 4))
        FUN_001a4670();
    return g_igCamera_metaObject[0];
}
