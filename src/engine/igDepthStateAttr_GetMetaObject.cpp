#include "dw4/reflected.h"
extern igMetaObject *g_igDepthStateAttr_metaObject[4];
extern "C" {
void FUN_00138570(void);
igMetaObject *igDepthStateAttr_GetMetaObject(void);
}
igMetaObject *igDepthStateAttr_GetMetaObject(void)
{
    igMetaObject *g = g_igDepthStateAttr_metaObject[0];
    if (!g || ((g->_validity & 4) != 0) == false)
        FUN_00138570();
    return g_igDepthStateAttr_metaObject[0];
}
