#include "dw4/reflected.h"
extern igMetaObject *g_igVertexArray2_metaObject[4];
extern "C" {
void FUN_0014ab70(void);
igMetaObject *igVertexArray2_GetMetaObject(void);
}
igMetaObject *igVertexArray2_GetMetaObject(void)
{
    igMetaObject *g = g_igVertexArray2_metaObject[0];
    if (!g || ((g->_validity & 4) != 0) == false)
        FUN_0014ab70();
    return g_igVertexArray2_metaObject[0];
}
