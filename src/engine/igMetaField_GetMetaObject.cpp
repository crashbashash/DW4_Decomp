#include "dw4/reflected.h"
extern igMetaObject *g_igMetaField_metaObject[4];
extern "C" {
void FUN_002bed40(void);
igMetaObject *igMetaField_GetMetaObject(void);
}
igMetaObject *igMetaField_GetMetaObject(void)
{
    igMetaObject *g = g_igMetaField_metaObject[0];
    if (!g || ((g->_validity & 4) != 0) == false)
        FUN_002bed40();
    return g_igMetaField_metaObject[0];
}
