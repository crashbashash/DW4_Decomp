#include "dw4/reflected.h"
extern igMetaObject *g_igColorAttr_metaObject[4];
extern "C" {
void FUN_00139000(void);
igMetaObject *igColorAttr_GetMetaObject(void);
}
igMetaObject *igColorAttr_GetMetaObject(void)
{
    igMetaObject *g = g_igColorAttr_metaObject[0];
    bool t;
    if (!g || !(t = g->_validity & 4))
        FUN_00139000();
    return g_igColorAttr_metaObject[0];
}
