#include "dw4/reflected.h"
extern igMetaObject *g_igPointSpriteExt_metaObject[4];
extern "C" {
void FUN_0014c670(void);
igMetaObject *igPointSpriteExt_GetMetaObject(void);
}
igMetaObject *igPointSpriteExt_GetMetaObject(void)
{
    igMetaObject *g = g_igPointSpriteExt_metaObject[0];
    bool t;
    if (!g || !(t = g->_validity & 4))
        FUN_0014c670();
    return g_igPointSpriteExt_metaObject[0];
}
