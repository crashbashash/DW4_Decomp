#include "dw4/reflected.h"
extern igMetaObject *g_igBlendMatrixSelect_metaObject[4];
extern "C" {
void FUN_001a4c50(void);
igMetaObject *igBlendMatrixSelect_GetMetaObject(void);
}
igMetaObject *igBlendMatrixSelect_GetMetaObject(void)
{
    igMetaObject *g = g_igBlendMatrixSelect_metaObject[0];
    if (!g || ((g->_validity & 4) != 0) == false)
        FUN_001a4c50();
    return g_igBlendMatrixSelect_metaObject[0];
}
