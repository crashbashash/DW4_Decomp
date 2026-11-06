#include "dw4/reflected.h"
extern igMetaObject *g_igUnsignedCharMetaField_metaObject[4];
extern "C" {
void igUnsignedCharMetaField_EnsureRegistered(void);
igMetaObject *igUnsignedCharMetaField_GetMetaObject(void);
}
igMetaObject *igUnsignedCharMetaField_GetMetaObject(void)
{
    igMetaObject *g = g_igUnsignedCharMetaField_metaObject[0];
    if (!g || ((g->_validity & 4) != 0) == false)
        igUnsignedCharMetaField_EnsureRegistered();
    return g_igUnsignedCharMetaField_metaObject[0];
}
