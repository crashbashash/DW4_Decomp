#include "dw4/reflected.h"
extern igMetaObject *g_igPsx2DecalExt_metaObject[4];
extern "C" {
void FUN_001542b0(void);
igMetaObject *igPsx2DecalExt_GetMetaObject(void);
}
igMetaObject *igPsx2DecalExt_GetMetaObject(void)
{
    igMetaObject *g = g_igPsx2DecalExt_metaObject[0];
    bool t;
    if (!g || !(t = g->_validity & 4))
        FUN_001542b0();
    return g_igPsx2DecalExt_metaObject[0];
}
