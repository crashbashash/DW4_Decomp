#include "dw4/reflected.h"
extern igMetaObject *g_igBlendListRecord_metaObject[4];
extern "C" {
void FUN_001a2d90(void);
igMetaObject *igBlendListRecord_GetMetaObject(void);
}
igMetaObject *igBlendListRecord_GetMetaObject(void)
{
    igMetaObject *g = g_igBlendListRecord_metaObject[0];
    bool t;
    if (!g || !(t = g->_validity & 4))
        FUN_001a2d90();
    return g_igBlendListRecord_metaObject[0];
}
