#include "dw4/reflected.h"
extern igMetaObject *g_igUnsignedIntMetaField_metaObject[4];
extern "C" {
void igUnsignedIntMetaField_EnsureRegistered(void);
igMetaObject *igUnsignedIntMetaField_GetMetaObject(void);
}
igMetaObject *igUnsignedIntMetaField_GetMetaObject(void)
{
    igMetaObject *g = g_igUnsignedIntMetaField_metaObject[0];
    if (!g || ((g->_validity & 4) != 0) == false)
        igUnsignedIntMetaField_EnsureRegistered();
    return g_igUnsignedIntMetaField_metaObject[0];
}
