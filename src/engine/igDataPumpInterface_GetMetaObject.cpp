#include "dw4/reflected.h"
extern igMetaObject *g_igDataPumpInterface_metaObject[4];
extern "C" {
void FUN_001e55d0(void);
igMetaObject *igDataPumpInterface_GetMetaObject(void);
}
igMetaObject *igDataPumpInterface_GetMetaObject(void)
{
    igMetaObject *g = g_igDataPumpInterface_metaObject[0];
    bool t;
    if (!g || !(t = g->_validity & 4))
        FUN_001e55d0();
    return g_igDataPumpInterface_metaObject[0];
}
