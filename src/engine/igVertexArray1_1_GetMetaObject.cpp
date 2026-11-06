#include "dw4/reflected.h"
extern igMetaObject *g_igVertexArray1_1_metaObject[4];
extern "C" {
void FUN_0014b710(void);
igMetaObject *igVertexArray1_1_GetMetaObject(void);
}
igMetaObject *igVertexArray1_1_GetMetaObject(void)
{
    igMetaObject *g = g_igVertexArray1_1_metaObject[0];
    bool t;
    if (!g || !(t = g->_validity & 4))
        FUN_0014b710();
    return g_igVertexArray1_1_metaObject[0];
}
