#include "dw4/reflected.h"
extern igMetaObject *g_igEnumMetaField_metaObject[4];
extern "C" {
void igEnumMetaField_EnsureRegistered(void);
igMetaObject *igEnumMetaField_GetMetaObject(void);
}
igMetaObject *igEnumMetaField_GetMetaObject(void)
{
    igMetaObject *g = g_igEnumMetaField_metaObject[0];
    if (!g || ((g->_validity & 4) != 0) == false)
        igEnumMetaField_EnsureRegistered();
    return g_igEnumMetaField_metaObject[0];
}
