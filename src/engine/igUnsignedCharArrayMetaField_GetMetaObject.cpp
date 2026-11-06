#include "dw4/reflected.h"
extern igMetaObject *g_igUnsignedCharArrayMetaField_metaObject[4];
extern "C" {
void FUN_002b77c0(void);
igMetaObject *igUnsignedCharArrayMetaField_GetMetaObject(void);
}
igMetaObject *igUnsignedCharArrayMetaField_GetMetaObject(void)
{
    igMetaObject *g = g_igUnsignedCharArrayMetaField_metaObject[0];
    bool t;
    if (!g || !(t = g->_validity & 4))
        FUN_002b77c0();
    return g_igUnsignedCharArrayMetaField_metaObject[0];
}
