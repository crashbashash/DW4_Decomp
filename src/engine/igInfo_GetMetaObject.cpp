#include "dw4/reflected.h"
extern igMetaObject *g_igInfo_metaObject[4];
extern "C" {
void FUN_002c3690(void);
igMetaObject *igInfo_GetMetaObject(void);
}
igMetaObject *igInfo_GetMetaObject(void)
{
    igMetaObject *g = g_igInfo_metaObject[0];
    if (!g || ((g->_validity & 4) != 0) == false)
        FUN_002c3690();
    return g_igInfo_metaObject[0];
}
