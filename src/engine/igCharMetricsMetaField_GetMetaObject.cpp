#include "dw4/reflected.h"
extern igMetaObject *g_igCharMetricsMetaField_metaObject[4];
extern "C" {
void igCharMetricsMetaField_RunStaticInit(void);
igMetaObject *igCharMetricsMetaField_GetMetaObject(void);
}
igMetaObject *igCharMetricsMetaField_GetMetaObject(void)
{
    igMetaObject *g = g_igCharMetricsMetaField_metaObject[0];
    bool t;
    if (!g || !(t = g->_validity & 4))
        igCharMetricsMetaField_RunStaticInit();
    return g_igCharMetricsMetaField_metaObject[0];
}
