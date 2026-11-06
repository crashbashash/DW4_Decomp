#include "dw4/reflected.h"
extern igMetaObject *g_igVertexStream_metaObject[4];
extern "C" {
void FUN_0014af80(void);
igMetaObject *igVertexStream_GetMetaObject(void);
}
igMetaObject *igVertexStream_GetMetaObject(void)
{
    igMetaObject *g = g_igVertexStream_metaObject[0];
    if (!g || ((g->_validity & 4) != 0) == false)
        FUN_0014af80();
    return g_igVertexStream_metaObject[0];
}
