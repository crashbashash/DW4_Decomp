#include "dw4/reflected.h"
extern igMetaObject *g_igTextureCubeAttr_metaObject[4];
extern "C" {
void FUN_00132420(void);
igMetaObject *igTextureCubeAttr_GetMetaObject(void);
}
igMetaObject *igTextureCubeAttr_GetMetaObject(void)
{
    igMetaObject *g = g_igTextureCubeAttr_metaObject[0];
    bool t;
    if (!g || !(t = g->_validity & 4))
        FUN_00132420();
    return g_igTextureCubeAttr_metaObject[0];
}
