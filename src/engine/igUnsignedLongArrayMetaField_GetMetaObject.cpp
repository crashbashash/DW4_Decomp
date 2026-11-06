#include "dw4/reflected.h"
extern igMetaObject *g_igUnsignedLongArrayMetaField_metaObject[4];
extern "C" {
void FUN_002b6b10(void);
igMetaObject *igUnsignedLongArrayMetaField_GetMetaObject(void);
}
igMetaObject *igUnsignedLongArrayMetaField_GetMetaObject(void)
{
    igMetaObject *g = g_igUnsignedLongArrayMetaField_metaObject[0];
    bool t;
    if (!g || !(t = g->_validity & 4))
        FUN_002b6b10();
    return g_igUnsignedLongArrayMetaField_metaObject[0];
}
