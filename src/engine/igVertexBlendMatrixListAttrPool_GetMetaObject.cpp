#include "dw4/reflected.h"
extern igMetaObject *g_igVertexBlendMatrixListAttrPool_metaObject[4];
extern "C" {
void FUN_00199f20(void);
igMetaObject *igVertexBlendMatrixListAttrPool_GetMetaObject(void);
}
igMetaObject *igVertexBlendMatrixListAttrPool_GetMetaObject(void)
{
    igMetaObject *g = g_igVertexBlendMatrixListAttrPool_metaObject[0];
    bool t;
    if (!g || !(t = g->_validity & 4))
        FUN_00199f20();
    return g_igVertexBlendMatrixListAttrPool_metaObject[0];
}
