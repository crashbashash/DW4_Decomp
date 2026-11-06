#include "dw4/reflected.h"
extern igMetaObject *g_igVertexDataList_metaObject[4];
extern "C" {
void FUN_0014b2a0(void);
igMetaObject *igVertexDataList_GetMetaObject(void);
}
igMetaObject *igVertexDataList_GetMetaObject(void)
{
    igMetaObject *g = g_igVertexDataList_metaObject[0];
    if (!g || ((g->_validity & 4) != 0) == false)
        FUN_0014b2a0();
    return g_igVertexDataList_metaObject[0];
}
