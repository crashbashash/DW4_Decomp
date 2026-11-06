#include "dw4/reflected.h"
extern igMetaObject *g_igCharMetricsList_metaObject[4];
extern "C" {
void igCharMetricsList_RunStaticInit(void);
igMetaObject *igCharMetricsList_GetMetaObject(void);
}
igMetaObject *igCharMetricsList_GetMetaObject(void)
{
    igMetaObject *g = g_igCharMetricsList_metaObject[0];
    bool t;
    if (!g || !(t = g->_validity & 4))
        igCharMetricsList_RunStaticInit();
    return g_igCharMetricsList_metaObject[0];
}
