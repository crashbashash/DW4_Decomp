#include "dw4/reflected.h"
extern igMetaObject *g_igModelViewMatrixAttrPool_metaObject[4];
extern "C" {
void FUN_0019a4e0(void);
igMetaObject *igModelViewMatrixAttrPool_GetMetaObject(void);
}
igMetaObject *igModelViewMatrixAttrPool_GetMetaObject(void)
{
    igMetaObject *g = g_igModelViewMatrixAttrPool_metaObject[0];
    bool t;
    if (!g || !(t = g->_validity & 4))
        FUN_0019a4e0();
    return g_igModelViewMatrixAttrPool_metaObject[0];
}
