#include "dw4/reflected.h"
extern igMetaObject *g_igMultiPassStateAttr_metaObject[4];
extern "C" {
void FUN_001352b0(void);
igMetaObject *igMultiPassStateAttr_GetMetaObject(void);
}
igMetaObject *igMultiPassStateAttr_GetMetaObject(void)
{
    igMetaObject *g = g_igMultiPassStateAttr_metaObject[0];
    if (!g || ((g->_validity & 4) != 0) == false)
        FUN_001352b0();
    return g_igMultiPassStateAttr_metaObject[0];
}
