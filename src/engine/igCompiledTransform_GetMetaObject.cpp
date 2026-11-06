#include "dw4/reflected.h"
extern igMetaObject *g_igCompiledTransform_metaObject[4];
extern "C" {
void FUN_001a3700(void);
igMetaObject *igCompiledTransform_GetMetaObject(void);
}
igMetaObject *igCompiledTransform_GetMetaObject(void)
{
    igMetaObject *g = g_igCompiledTransform_metaObject[0];
    if (!g || ((g->_validity & 4) != 0) == false)
        FUN_001a3700();
    return g_igCompiledTransform_metaObject[0];
}
