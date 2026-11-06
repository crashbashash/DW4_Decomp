#include "dw4/reflected.h"
extern igMetaObject *g_igBlendStateAttr_metaObject[4];
extern "C" {
void FUN_00139720(void);
igMetaObject *igBlendStateAttr_GetMetaObject(void);
}
igMetaObject *igBlendStateAttr_GetMetaObject(void)
{
    igMetaObject *g = g_igBlendStateAttr_metaObject[0];
    bool t;
    if (!g || !(t = g->_validity & 4))
        FUN_00139720();
    return g_igBlendStateAttr_metaObject[0];
}
