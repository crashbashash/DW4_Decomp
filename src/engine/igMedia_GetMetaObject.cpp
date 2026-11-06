#include "dw4/reflected.h"
extern igMetaObject *g_igMedia_metaObject[4];
extern "C" {
void FUN_002c1780(void);
igMetaObject *igMedia_GetMetaObject(void);
}
igMetaObject *igMedia_GetMetaObject(void)
{
    igMetaObject *g = g_igMedia_metaObject[0];
    if (!g || ((g->_validity & 4) != 0) == false)
        FUN_002c1780();
    return g_igMedia_metaObject[0];
}
