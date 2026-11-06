#include "dw4/reflected.h"
extern igMetaObject *g_igModelViewMatrixBoneSelectList_metaObject_00561880[4];
extern "C" {
void FUN_0019d360(void);
igMetaObject *igModelViewMatrixBoneSelectList_561880_GetMetaObject(void);
}
igMetaObject *igModelViewMatrixBoneSelectList_561880_GetMetaObject(void)
{
    igMetaObject *g = g_igModelViewMatrixBoneSelectList_metaObject_00561880[0];
    bool t;
    if (!g || !(t = g->_validity & 4))
        FUN_0019d360();
    return g_igModelViewMatrixBoneSelectList_metaObject_00561880[0];
}
