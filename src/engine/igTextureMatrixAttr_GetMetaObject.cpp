#include "dw4/reflected.h"
extern igMetaObject *g_igTextureMatrixAttr_metaObject[4];
extern "C" {
void FUN_001318f0(void);
igMetaObject *igTextureMatrixAttr_GetMetaObject(void);
}
igMetaObject *igTextureMatrixAttr_GetMetaObject(void)
{
    igMetaObject *g = g_igTextureMatrixAttr_metaObject[0];
    if (!g || ((g->_validity & 4) != 0) == false)
        FUN_001318f0();
    return g_igTextureMatrixAttr_metaObject[0];
}
