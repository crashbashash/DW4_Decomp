#include "dw4/reflected.h"
extern igMetaObject *g_igBlendMatrixPaletteAttr_metaObject[4];
extern "C" {
void FUN_00139ab0(void);
igMetaObject *igBlendMatrixPaletteAttr_GetMetaObject(void);
}
igMetaObject *igBlendMatrixPaletteAttr_GetMetaObject(void)
{
    igMetaObject *g = g_igBlendMatrixPaletteAttr_metaObject[0];
    bool t;
    if (!g || !(t = g->_validity & 4))
        FUN_00139ab0();
    return g_igBlendMatrixPaletteAttr_metaObject[0];
}
