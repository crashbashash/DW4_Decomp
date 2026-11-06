#include "dw4/reflected.h"
extern igMetaObject *g_igMultiTextureExt_metaObject[4];
extern "C" {
void FUN_0014d5c0(void);
igMetaObject *igMultiTextureExt_GetMetaObject(void);
}
igMetaObject *igMultiTextureExt_GetMetaObject(void)
{
    igMetaObject *g = g_igMultiTextureExt_metaObject[0];
    bool t;
    if (!g || !(t = g->_validity & 4))
        FUN_0014d5c0();
    return g_igMultiTextureExt_metaObject[0];
}
