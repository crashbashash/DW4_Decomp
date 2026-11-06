#include "dw4/reflected.h"
extern igMetaObject *g_igMaterialAttr_metaObject[4];
extern "C" {
void FUN_00135c70(void);
igMetaObject *igMaterialAttr_GetMetaObject(void);
}
igMetaObject *igMaterialAttr_GetMetaObject(void)
{
    igMetaObject *g = g_igMaterialAttr_metaObject[0];
    bool t;
    if (!g || !(t = g->_validity & 4))
        FUN_00135c70();
    return g_igMaterialAttr_metaObject[0];
}
