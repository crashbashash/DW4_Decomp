#include "dw4/reflected.h"
extern igMetaObject *g_igLongMetaField_metaObject[4];
extern "C" {
void FUN_002c1b10(void);
igMetaObject *igLongMetaField_GetMetaObject(void);
}
igMetaObject *igLongMetaField_GetMetaObject(void)
{
    igMetaObject *g = g_igLongMetaField_metaObject[0];
    bool t;
    if (!g || !(t = g->_validity & 4))
        FUN_002c1b10();
    return g_igLongMetaField_metaObject[0];
}
