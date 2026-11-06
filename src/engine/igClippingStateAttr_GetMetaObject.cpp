#include "dw4/reflected.h"
extern igMetaObject *g_igClippingStateAttr_metaObject[4];
extern "C" {
void FUN_00139250(void);
igMetaObject *igClippingStateAttr_GetMetaObject(void);
}
igMetaObject *igClippingStateAttr_GetMetaObject(void)
{
    igMetaObject *g = g_igClippingStateAttr_metaObject[0];
    if (!g || ((g->_validity & 4) != 0) == false)
        FUN_00139250();
    return g_igClippingStateAttr_metaObject[0];
}
