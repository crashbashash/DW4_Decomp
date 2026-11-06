#include "dw4/reflected.h"
extern igMetaObject *g_igUnsignedShortMetaField_metaObject[4];
extern "C" {
void FUN_002b61d0(void);
igMetaObject *igUnsignedShortMetaField_GetMetaObject(void);
}
igMetaObject *igUnsignedShortMetaField_GetMetaObject(void)
{
    igMetaObject *g = g_igUnsignedShortMetaField_metaObject[0];
    bool t;
    if (!g || !(t = g->_validity & 4))
        FUN_002b61d0();
    return g_igUnsignedShortMetaField_metaObject[0];
}
