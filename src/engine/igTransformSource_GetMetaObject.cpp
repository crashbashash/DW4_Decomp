#include "dw4/reflected.h"
extern igMetaObject *g_igTransformSource_metaObject[4];
extern "C" {
void FUN_00194e70(void);
igMetaObject *igTransformSource_GetMetaObject(void);
}
igMetaObject *igTransformSource_GetMetaObject(void)
{
    igMetaObject *g = g_igTransformSource_metaObject[0];
    bool t;
    if (!g || !(t = g->_validity & 4))
        FUN_00194e70();
    return g_igTransformSource_metaObject[0];
}
