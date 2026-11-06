#include "dw4/reflected.h"
extern igMetaObject *g_igVertexArray2Helper_metaObject[4];
extern "C" {
void FUN_0014a640(void);
igMetaObject *igVertexArray2Helper_GetMetaObject(void);
}
igMetaObject *igVertexArray2Helper_GetMetaObject(void)
{
    igMetaObject *g = g_igVertexArray2Helper_metaObject[0];
    if (!g || ((g->_validity & 4) != 0) == false)
        FUN_0014a640();
    return g_igVertexArray2Helper_metaObject[0];
}
