#include "dw4/reflected.h"
extern igMetaObject *g_igVertexBlendMatrixListAttr_metaObject[4];
extern "C" {
void FUN_00130a70(void);
igMetaObject *igVertexBlendMatrixListAttr_GetMetaObject(void);
}
igMetaObject *igVertexBlendMatrixListAttr_GetMetaObject(void)
{
    igMetaObject *g = g_igVertexBlendMatrixListAttr_metaObject[0];
    if (!g || ((g->_validity & 4) != 0) == false)
        FUN_00130a70();
    return g_igVertexBlendMatrixListAttr_metaObject[0];
}
