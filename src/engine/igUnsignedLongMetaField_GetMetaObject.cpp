#include "dw4/reflected.h"
extern igMetaObject *g_igUnsignedLongMetaField_metaObject[4];
extern "C" {
void FUN_002b6890(void);
igMetaObject *igUnsignedLongMetaField_GetMetaObject(void);
}
igMetaObject *igUnsignedLongMetaField_GetMetaObject(void)
{
    igMetaObject *g = g_igUnsignedLongMetaField_metaObject[0];
    bool t;
    if (!g || !(t = g->_validity & 4))
        FUN_002b6890();
    return g_igUnsignedLongMetaField_metaObject[0];
}
