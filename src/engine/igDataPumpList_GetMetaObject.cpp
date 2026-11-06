#include "dw4/reflected.h"
extern igMetaObject *g_igDataPumpList_metaObject[4];
extern "C" {
void FUN_001e54a0(void);
igMetaObject *igDataPumpList_GetMetaObject(void);
}
igMetaObject *igDataPumpList_GetMetaObject(void)
{
    igMetaObject *g = g_igDataPumpList_metaObject[0];
    bool t;
    if (!g || !(t = g->_validity & 4))
        FUN_001e54a0();
    return g_igDataPumpList_metaObject[0];
}
