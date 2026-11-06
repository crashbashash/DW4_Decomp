#include "dw4/reflected.h"
extern igMetaObject *g_igVertexBlendMatrixAttrPool_metaObject[4];
extern "C" {
void FUN_0019a090(void);
igMetaObject *igVertexBlendMatrixAttrPool_GetMetaObject(void);
}
igMetaObject *igVertexBlendMatrixAttrPool_GetMetaObject(void)
{
    igMetaObject *g = g_igVertexBlendMatrixAttrPool_metaObject[0];
    if (!g || ((g->_validity & 4) != 0) == false)
        FUN_0019a090();
    return g_igVertexBlendMatrixAttrPool_metaObject[0];
}
