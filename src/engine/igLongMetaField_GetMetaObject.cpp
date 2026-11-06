#include "dw4/reflected.h"
extern igMetaObject *g_igLongMetaField_metaObject[4];
extern "C" {
void FUN_002c1b10(void);
igMetaObject *igLongMetaField_GetMetaObject(void);
}
igMetaObject *igLongMetaField_GetMetaObject(void)
{
    igMetaObject *g = g_igLongMetaField_metaObject[0];
    if (!g || ((g->_validity & 4) != 0) == false)
        FUN_002c1b10();
    return g_igLongMetaField_metaObject[0];
}
