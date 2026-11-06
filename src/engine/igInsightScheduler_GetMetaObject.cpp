#include "dw4/reflected.h"
extern igMetaObject *g_igInsightScheduler_metaObject[4];
extern "C" {
void FUN_00232510(void);
igMetaObject *igInsightScheduler_GetMetaObject(void);
}
igMetaObject *igInsightScheduler_GetMetaObject(void)
{
    igMetaObject *g = g_igInsightScheduler_metaObject[0];
    if (!g || ((g->_validity & 4) != 0) == false)
        FUN_00232510();
    return g_igInsightScheduler_metaObject[0];
}
