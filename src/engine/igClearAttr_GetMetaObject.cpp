#include "dw4/reflected.h"
extern igMetaObject *g_igClearAttr_metaObject[4];
extern "C" {
void FUN_00139440(void);
igMetaObject *igClearAttr_GetMetaObject(void);
}
igMetaObject *igClearAttr_GetMetaObject(void)
{
    igMetaObject *g = g_igClearAttr_metaObject[0];
    bool t;
    if (!g || !(t = g->_validity & 4))
        FUN_00139440();
    return g_igClearAttr_metaObject[0];
}
