#include "dw4/reflected.h"
extern igMetaObject *g_igTextureList_metaObject[4];
extern "C" {
void FUN_0013a440(void);
igMetaObject *igTextureList_GetMetaObject(void);
}
igMetaObject *igTextureList_GetMetaObject(void)
{
    igMetaObject *g = g_igTextureList_metaObject[0];
    if (!g || ((g->_validity & 4) != 0) == false)
        FUN_0013a440();
    return g_igTextureList_metaObject[0];
}
