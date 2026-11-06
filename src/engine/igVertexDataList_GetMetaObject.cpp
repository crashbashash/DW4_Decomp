#include "dw4/reflected.h"
extern igMetaObject *g_igVertexDataList_metaObject[4];
extern "C" {
void FUN_0014b2a0(void);
igMetaObject *igVertexDataList_GetMetaObject(void);
}
igMetaObject *igVertexDataList_GetMetaObject(void)
{
    igMetaObject *g = g_igVertexDataList_metaObject[0];
    bool t;
    if (!g || !(t = g->_validity & 4))
        FUN_0014b2a0();
    return g_igVertexDataList_metaObject[0];
}
