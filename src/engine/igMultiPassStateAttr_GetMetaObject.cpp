#include "dw4/reflected.h"
extern igMetaObject *g_igMultiPassStateAttr_metaObject[4];
extern "C" {
void FUN_001352b0(void);
igMetaObject *igMultiPassStateAttr_GetMetaObject(void);
}
igMetaObject *igMultiPassStateAttr_GetMetaObject(void)
{
    igMetaObject *g = g_igMultiPassStateAttr_metaObject[0];
    bool t;
    if (!g || !(t = g->_validity & 4))
        FUN_001352b0();
    return g_igMultiPassStateAttr_metaObject[0];
}
