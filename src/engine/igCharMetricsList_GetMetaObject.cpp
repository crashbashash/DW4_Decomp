#include "dw4/reflected.h"
extern igMetaObject *g_igCharMetricsList_metaObject[4];
extern "C" {
void igCharMetricsList_RunStaticInit(void);
igMetaObject *igCharMetricsList_GetMetaObject(void);
}
igMetaObject *igCharMetricsList_GetMetaObject(void)
{
    igMetaObject *g = g_igCharMetricsList_metaObject[0];
    if (!g || ((g->_validity & 4) != 0) == false)
        igCharMetricsList_RunStaticInit();
    return g_igCharMetricsList_metaObject[0];
}
