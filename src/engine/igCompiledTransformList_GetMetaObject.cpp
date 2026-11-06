#include "dw4/reflected.h"
extern igMetaObject *g_igCompiledTransformList_metaObject[4];
extern "C" {
void FUN_001a3500(void);
igMetaObject *igCompiledTransformList_GetMetaObject(void);
}
igMetaObject *igCompiledTransformList_GetMetaObject(void)
{
    igMetaObject *g = g_igCompiledTransformList_metaObject[0];
    if (!g || ((g->_validity & 4) != 0) == false)
        FUN_001a3500();
    return g_igCompiledTransformList_metaObject[0];
}
