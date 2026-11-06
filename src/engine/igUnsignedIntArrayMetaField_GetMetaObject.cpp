#include "dw4/reflected.h"
extern igMetaObject *g_igUnsignedIntArrayMetaField_metaObject[4];
extern "C" {
void FUN_002b71d0(void);
igMetaObject *igUnsignedIntArrayMetaField_GetMetaObject(void);
}
igMetaObject *igUnsignedIntArrayMetaField_GetMetaObject(void)
{
    igMetaObject *g = g_igUnsignedIntArrayMetaField_metaObject[0];
    bool t;
    if (!g || !(t = g->_validity & 4))
        FUN_002b71d0();
    return g_igUnsignedIntArrayMetaField_metaObject[0];
}
