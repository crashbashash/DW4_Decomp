#include "dw4/reflected.h"
extern igMetaObject *g_igObjectRefMetaField_metaObject[4];
extern "C" {
void igObjectRefMetaField_EnsureRegistered(void);
igMetaObject *igObjectRefMetaField_GetMetaObject(void);
}
igMetaObject *igObjectRefMetaField_GetMetaObject(void)
{
    igMetaObject *g = g_igObjectRefMetaField_metaObject[0];
    if (!g || ((g->_validity & 4) != 0) == false)
        igObjectRefMetaField_EnsureRegistered();
    return g_igObjectRefMetaField_metaObject[0];
}
