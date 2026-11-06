#include "dw4/reflected.h"
extern igMetaObject *g_igTextureMatrixAttrPool_metaObject[4];
extern "C" {
void FUN_00199c40(void);
igMetaObject *igTextureMatrixAttrPool_GetMetaObject(void);
}
igMetaObject *igTextureMatrixAttrPool_GetMetaObject(void)
{
    igMetaObject *g = g_igTextureMatrixAttrPool_metaObject[0];
    if (!g || ((g->_validity & 4) != 0) == false)
        FUN_00199c40();
    return g_igTextureMatrixAttrPool_metaObject[0];
}
