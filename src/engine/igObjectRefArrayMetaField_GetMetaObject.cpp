#include "dw4/reflected.h"
extern igMetaObject *g_igObjectRefArrayMetaField_metaObject[4];
extern "C" {
void FUN_002bd470(void);
igMetaObject *igObjectRefArrayMetaField_GetMetaObject(void);
}
igMetaObject *igObjectRefArrayMetaField_GetMetaObject(void)
{
    igMetaObject *g = g_igObjectRefArrayMetaField_metaObject[0];
    if (!g || ((g->_validity & 4) != 0) == false)
        FUN_002bd470();
    return g_igObjectRefArrayMetaField_metaObject[0];
}
