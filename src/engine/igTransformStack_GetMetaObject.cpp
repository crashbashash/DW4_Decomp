#include "dw4/reflected.h"
extern igMetaObject *g_igTransformStack_metaObject[4];
extern "C" {
void FUN_001960c0(void);
igMetaObject *igTransformStack_GetMetaObject(void);
}
igMetaObject *igTransformStack_GetMetaObject(void)
{
    igMetaObject *g = g_igTransformStack_metaObject[0];
    bool t;
    if (!g || !(t = g->_validity & 4))
        FUN_001960c0();
    return g_igTransformStack_metaObject[0];
}
