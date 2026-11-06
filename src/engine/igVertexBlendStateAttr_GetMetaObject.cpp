#include "dw4/reflected.h"
extern igMetaObject *g_igVertexBlendStateAttr_metaObject[4];
extern "C" {
void FUN_00130830(void);
igMetaObject *igVertexBlendStateAttr_GetMetaObject(void);
}
igMetaObject *igVertexBlendStateAttr_GetMetaObject(void)
{
    igMetaObject *g = g_igVertexBlendStateAttr_metaObject[0];
    if (!g || ((g->_validity & 4) != 0) == false)
        FUN_00130830();
    return g_igVertexBlendStateAttr_metaObject[0];
}
