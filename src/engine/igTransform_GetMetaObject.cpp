#include "dw4/reflected.h"
extern igMetaObject *g_igTransform_metaObject[4];
extern "C" {
void FUN_001964d0(void);
igMetaObject *igTransform_GetMetaObject(void);
}
igMetaObject *igTransform_GetMetaObject(void)
{
    igMetaObject *g = g_igTransform_metaObject[0];
    bool t;
    if (!g || !(t = g->_validity & 4))
        FUN_001964d0();
    return g_igTransform_metaObject[0];
}
