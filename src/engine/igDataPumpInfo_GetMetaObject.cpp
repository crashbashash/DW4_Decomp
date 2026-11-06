#include "dw4/reflected.h"
extern igMetaObject *g_igDataPumpInfo_metaObject[4];
extern "C" {
void FUN_001e5810(void);
igMetaObject *igDataPumpInfo_GetMetaObject(void);
}
igMetaObject *igDataPumpInfo_GetMetaObject(void)
{
    igMetaObject *g = g_igDataPumpInfo_metaObject[0];
    if (!g || ((g->_validity & 4) != 0) == false)
        FUN_001e5810();
    return g_igDataPumpInfo_metaObject[0];
}
