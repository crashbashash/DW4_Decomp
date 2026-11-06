#include "dw4/reflected.h"
extern igMetaObject *g_igCompoundMetaField_metaObject[4];
extern "C" {
void FUN_002cbd40(void);
igMetaObject *igCompoundMetaField_GetMetaObject(void);
}
igMetaObject *igCompoundMetaField_GetMetaObject(void)
{
    igMetaObject *g = g_igCompoundMetaField_metaObject[0];
    if (!g || ((g->_validity & 4) != 0) == false)
        FUN_002cbd40();
    return g_igCompoundMetaField_metaObject[0];
}
