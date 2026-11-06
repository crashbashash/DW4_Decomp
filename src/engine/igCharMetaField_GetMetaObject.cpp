#include "dw4/reflected.h"
extern igMetaObject *g_igCharMetaField_metaObject[4];
extern "C" {
void FUN_002cc160(void);
igMetaObject *igCharMetaField_GetMetaObject(void);
}
igMetaObject *igCharMetaField_GetMetaObject(void)
{
    igMetaObject *g = g_igCharMetaField_metaObject[0];
    if (!g || ((g->_validity & 4) != 0) == false)
        FUN_002cc160();
    return g_igCharMetaField_metaObject[0];
}
