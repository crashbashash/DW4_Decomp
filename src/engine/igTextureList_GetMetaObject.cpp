#include "dw4/reflected.h"
extern igMetaObject *g_igTextureList_metaObject[4];
extern "C" {
void FUN_0013a440(void);
igMetaObject *igTextureList_GetMetaObject(void);
}
igMetaObject *igTextureList_GetMetaObject(void)
{
    igMetaObject *g = g_igTextureList_metaObject[0];
    bool t;
    if (!g || !(t = g->_validity & 4))
        FUN_0013a440();
    return g_igTextureList_metaObject[0];
}
