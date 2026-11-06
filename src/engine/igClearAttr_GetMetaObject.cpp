#include "dw4/reflected.h"
extern igMetaObject *g_igClearAttr_metaObject[4];
extern "C" {
void FUN_00139440(void);
igMetaObject *igClearAttr_GetMetaObject(void);
}
igMetaObject *igClearAttr_GetMetaObject(void)
{
    igMetaObject *g = g_igClearAttr_metaObject[0];
    if (!g || ((g->_validity & 4) != 0) == false)
        FUN_00139440();
    return g_igClearAttr_metaObject[0];
}
