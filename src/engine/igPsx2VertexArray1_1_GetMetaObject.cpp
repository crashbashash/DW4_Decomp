#include "dw4/reflected.h"
extern igMetaObject *g_igPsx2VertexArray1_1_metaObject[4];
extern "C" {
void FUN_001525e0(void);
igMetaObject *igPsx2VertexArray1_1_GetMetaObject(void);
}
igMetaObject *igPsx2VertexArray1_1_GetMetaObject(void)
{
    igMetaObject *g = g_igPsx2VertexArray1_1_metaObject[0];
    if (!g || ((g->_validity & 4) != 0) == false)
        FUN_001525e0();
    return g_igPsx2VertexArray1_1_metaObject[0];
}
