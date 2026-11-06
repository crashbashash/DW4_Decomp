#include "dw4/reflected.h"
extern igMetaObject *g_igInsightCore_metaObject[4];
extern "C" {
void FUN_00232de0(void);
igMetaObject *igInsightCore_GetMetaObject(void);
}
igMetaObject *igInsightCore_GetMetaObject(void)
{
    igMetaObject *g = g_igInsightCore_metaObject[0];
    if (!g || ((g->_validity & 4) != 0) == false)
        FUN_00232de0();
    return g_igInsightCore_metaObject[0];
}
