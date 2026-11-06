#include "dw4/reflected.h"
extern igMetaObject *g_igVertexArray_metaObject[4];
extern "C" {
void FUN_0014ba20(void);
igMetaObject *igVertexArray_GetMetaObject(void);
}
igMetaObject *igVertexArray_GetMetaObject(void)
{
    igMetaObject *g = g_igVertexArray_metaObject[0];
    bool t;
    if (!g || !(t = g->_validity & 4))
        FUN_0014ba20();
    return g_igVertexArray_metaObject[0];
}
