#include "dw4/reflected.h"
extern igMetaObject *g_igFogStateAttr_metaObject[4];
extern "C" {
void FUN_00137ca0(void);
igMetaObject *igFogStateAttr_GetMetaObject(void);
}
igMetaObject *igFogStateAttr_GetMetaObject(void)
{
    igMetaObject *g = g_igFogStateAttr_metaObject[0];
    if (!g || ((g->_validity & 4) != 0) == false)
        FUN_00137ca0();
    return g_igFogStateAttr_metaObject[0];
}
