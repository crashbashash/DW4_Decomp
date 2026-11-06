#include "dw4/reflected.h"
extern igMetaObject *g_igVertexBlendMatrixAttr_metaObject[4];
extern "C" {
void FUN_00130cf0(void);
igMetaObject *igVertexBlendMatrixAttr_GetMetaObject(void);
}
igMetaObject *igVertexBlendMatrixAttr_GetMetaObject(void)
{
    igMetaObject *g = g_igVertexBlendMatrixAttr_metaObject[0];
    bool t;
    if (!g || !(t = g->_validity & 4))
        FUN_00130cf0();
    return g_igVertexBlendMatrixAttr_metaObject[0];
}
