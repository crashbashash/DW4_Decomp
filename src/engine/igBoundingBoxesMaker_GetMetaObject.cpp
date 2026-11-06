#include "dw4/reflected.h"
extern igMetaObject *g_igBoundingBoxesMaker_metaObject[4];
extern "C" {
void FUN_001a4970(void);
igMetaObject *igBoundingBoxesMaker_GetMetaObject(void);
}
igMetaObject *igBoundingBoxesMaker_GetMetaObject(void)
{
    igMetaObject *g = g_igBoundingBoxesMaker_metaObject[0];
    if (!g || ((g->_validity & 4) != 0) == false)
        FUN_001a4970();
    return g_igBoundingBoxesMaker_metaObject[0];
}
