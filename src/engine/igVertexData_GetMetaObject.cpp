#include "dw4/reflected.h"
extern igMetaObject *g_igVertexData_metaObject[4];
extern "C" {
void FUN_0014b500(void);
igMetaObject *igVertexData_GetMetaObject(void);
}
igMetaObject *igVertexData_GetMetaObject(void)
{
    igMetaObject *g = g_igVertexData_metaObject[0];
    bool t;
    if (!g || !(t = g->_validity & 4))
        FUN_0014b500();
    return g_igVertexData_metaObject[0];
}
