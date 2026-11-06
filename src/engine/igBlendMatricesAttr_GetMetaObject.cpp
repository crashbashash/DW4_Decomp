#include "dw4/reflected.h"
extern igMetaObject *g_igBlendMatricesAttr_metaObject[4];
extern "C" {
void FUN_00139ce0(void);
igMetaObject *igBlendMatricesAttr_GetMetaObject(void);
}
igMetaObject *igBlendMatricesAttr_GetMetaObject(void)
{
    igMetaObject *g = g_igBlendMatricesAttr_metaObject[0];
    bool t;
    if (!g || !(t = g->_validity & 4))
        FUN_00139ce0();
    return g_igBlendMatricesAttr_metaObject[0];
}
