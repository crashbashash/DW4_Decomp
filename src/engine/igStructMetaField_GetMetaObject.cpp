#include "dw4/reflected.h"
extern igMetaObject *g_igStructMetaField_metaObject[4];
extern "C" {
void FUN_002b8ab0(void);
igMetaObject *igStructMetaField_GetMetaObject(void);
}
igMetaObject *igStructMetaField_GetMetaObject(void)
{
    igMetaObject *g = g_igStructMetaField_metaObject[0];
    bool t;
    if (!g || !(t = g->_validity & 4))
        FUN_002b8ab0();
    return g_igStructMetaField_metaObject[0];
}
