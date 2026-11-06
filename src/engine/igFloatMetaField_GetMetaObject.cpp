#include "dw4/reflected.h"
extern igMetaObject *g_igFloatMetaField_metaObject[4];
extern "C" {
void FUN_002c4710(void);
igMetaObject *igFloatMetaField_GetMetaObject(void);
}
igMetaObject *igFloatMetaField_GetMetaObject(void)
{
    igMetaObject *g = g_igFloatMetaField_metaObject[0];
    if (!g || ((g->_validity & 4) != 0) == false)
        FUN_002c4710();
    return g_igFloatMetaField_metaObject[0];
}
