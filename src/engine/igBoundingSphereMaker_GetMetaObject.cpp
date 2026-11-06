#include "dw4/reflected.h"
extern igMetaObject *g_igBoundingSphereMaker_metaObject[4];
extern "C" {
void FUN_0023aaf0(void);
igMetaObject *igBoundingSphereMaker_GetMetaObject(void);
}
igMetaObject *igBoundingSphereMaker_GetMetaObject(void)
{
    igMetaObject *g = g_igBoundingSphereMaker_metaObject[0];
    if (!g || ((g->_validity & 4) != 0) == false)
        FUN_0023aaf0();
    return g_igBoundingSphereMaker_metaObject[0];
}
