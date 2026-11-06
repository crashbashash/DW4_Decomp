#include "dw4/reflected.h"
extern igMetaObject *g_igInsightPlugin_metaObject[4];
extern "C" {
void FUN_00232780(void);
igMetaObject *igInsightPlugin_GetMetaObject(void);
}
igMetaObject *igInsightPlugin_GetMetaObject(void)
{
    igMetaObject *g = g_igInsightPlugin_metaObject[0];
    if (!g || ((g->_validity & 4) != 0) == false)
        FUN_00232780();
    return g_igInsightPlugin_metaObject[0];
}
