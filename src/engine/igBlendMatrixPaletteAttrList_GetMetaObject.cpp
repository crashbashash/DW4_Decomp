#include "dw4/reflected.h"
extern igMetaObject *g_igBlendMatrixPaletteAttrList_metaObject[4];
extern "C" {
void FUN_00139900(void);
igMetaObject *igBlendMatrixPaletteAttrList_GetMetaObject(void);
}
igMetaObject *igBlendMatrixPaletteAttrList_GetMetaObject(void)
{
    igMetaObject *g = g_igBlendMatrixPaletteAttrList_metaObject[0];
    bool t;
    if (!g || !(t = g->_validity & 4))
        FUN_00139900();
    return g_igBlendMatrixPaletteAttrList_metaObject[0];
}
