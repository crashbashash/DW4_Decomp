#include "dw4/reflected.h"
extern igMetaObject *g_igPsx2VertexStream_metaObject[4];
extern "C" {
void FUN_00152050(void);
igMetaObject *igPsx2VertexStream_GetMetaObject(void);
}
igMetaObject *igPsx2VertexStream_GetMetaObject(void)
{
    igMetaObject *g = g_igPsx2VertexStream_metaObject[0];
    bool t;
    if (!g || !(t = g->_validity & 4))
        FUN_00152050();
    return g_igPsx2VertexStream_metaObject[0];
}
