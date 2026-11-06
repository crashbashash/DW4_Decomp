#include "dw4/reflected.h"
extern igMetaObject *g_igVertexBlendMatrixListAttr_metaObject[4];
extern "C" {
void FUN_00130a70(void);
igMetaObject *igVertexBlendMatrixListAttr_GetMetaObject(void);
}
igMetaObject *igVertexBlendMatrixListAttr_GetMetaObject(void)
{
    igMetaObject *g = g_igVertexBlendMatrixListAttr_metaObject[0];
    bool t;
    if (!g || !(t = g->_validity & 4))
        FUN_00130a70();
    return g_igVertexBlendMatrixListAttr_metaObject[0];
}
