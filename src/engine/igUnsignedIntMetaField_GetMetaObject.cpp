#include "dw4/reflected.h"
extern igMetaObject *g_igUnsignedIntMetaField_metaObject[4];
extern "C" {
void igUnsignedIntMetaField_EnsureRegistered(void);
igMetaObject *igUnsignedIntMetaField_GetMetaObject(void);
}
igMetaObject *igUnsignedIntMetaField_GetMetaObject(void)
{
    igMetaObject *g = g_igUnsignedIntMetaField_metaObject[0];
    bool t;
    if (!g || !(t = g->_validity & 4))
        igUnsignedIntMetaField_EnsureRegistered();
    return g_igUnsignedIntMetaField_metaObject[0];
}
