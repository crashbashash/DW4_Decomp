#include "dw4/reflected.h"
extern igMetaObject *g_igImageMipMapList_metaObject[4];
extern "C" {
void FUN_001330d0(void);
igMetaObject *igImageMipMapList_GetMetaObject(void);
}
igMetaObject *igImageMipMapList_GetMetaObject(void)
{
    igMetaObject *g = g_igImageMipMapList_metaObject[0];
    if (!g || ((g->_validity & 4) != 0) == false)
        FUN_001330d0();
    return g_igImageMipMapList_metaObject[0];
}
