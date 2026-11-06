#include "dw4/reflected.h"
extern igMetaObject *g_igUnsignedShortArrayMetaField_metaObject[4];
extern "C" {
void FUN_002b6490(void);
igMetaObject *igUnsignedShortArrayMetaField_GetMetaObject(void);
}
igMetaObject *igUnsignedShortArrayMetaField_GetMetaObject(void)
{
    igMetaObject *g = g_igUnsignedShortArrayMetaField_metaObject[0];
    bool t;
    if (!g || !(t = g->_validity & 4))
        FUN_002b6490();
    return g_igUnsignedShortArrayMetaField_metaObject[0];
}
