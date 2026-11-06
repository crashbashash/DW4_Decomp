#include "dw4/reflected.h"
extern igMetaObject *g_igDepthWriteStateAttr_metaObject[4];
extern "C" {
void FUN_00138380(void);
igMetaObject *igDepthWriteStateAttr_GetMetaObject(void);
}
igMetaObject *igDepthWriteStateAttr_GetMetaObject(void)
{
    igMetaObject *g = g_igDepthWriteStateAttr_metaObject[0];
    if (!g || ((g->_validity & 4) != 0) == false)
        FUN_00138380();
    return g_igDepthWriteStateAttr_metaObject[0];
}
