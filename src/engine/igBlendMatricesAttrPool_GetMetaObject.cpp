#include "dw4/reflected.h"
extern igMetaObject *g_igBlendMatricesAttrPool_metaObject[4];
extern "C" {
void FUN_00199ad0(void);
igMetaObject *igBlendMatricesAttrPool_GetMetaObject(void);
}
igMetaObject *igBlendMatricesAttrPool_GetMetaObject(void)
{
    igMetaObject *g = g_igBlendMatricesAttrPool_metaObject[0];
    bool t;
    if (!g || !(t = g->_validity & 4))
        FUN_00199ad0();
    return g_igBlendMatricesAttrPool_metaObject[0];
}
