#include "dw4/reflected.h"
extern igMetaObject *g_igStencilStateAttr_metaObject[4];
extern "C" {
void FUN_00133510(void);
igMetaObject *igStencilStateAttr_GetMetaObject(void);
}
igMetaObject *igStencilStateAttr_GetMetaObject(void)
{
    igMetaObject *g = g_igStencilStateAttr_metaObject[0];
    bool t;
    if (!g || !(t = g->_validity & 4))
        FUN_00133510();
    return g_igStencilStateAttr_metaObject[0];
}
