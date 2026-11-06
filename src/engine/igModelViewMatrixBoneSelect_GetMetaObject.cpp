#include "dw4/reflected.h"
extern igMetaObject *g_igModelViewMatrixBoneSelect_metaObject[4];
extern "C" {
void FUN_0019d4f0(void);
igMetaObject *igModelViewMatrixBoneSelect_GetMetaObject(void);
}
igMetaObject *igModelViewMatrixBoneSelect_GetMetaObject(void)
{
    igMetaObject *g = g_igModelViewMatrixBoneSelect_metaObject[0];
    if (!g || ((g->_validity & 4) != 0) == false)
        FUN_0019d4f0();
    return g_igModelViewMatrixBoneSelect_metaObject[0];
}
