#include "dw4/reflected.h"
extern igMetaObject *g_igIntArrayMetaField_metaObject[4];
extern "C" {
void FUN_002c31f0(void);
igMetaObject *igIntArrayMetaField_GetMetaObject(void);
}
igMetaObject *igIntArrayMetaField_GetMetaObject(void)
{
    igMetaObject *g = g_igIntArrayMetaField_metaObject[0];
    if (!g || ((g->_validity & 4) != 0) == false)
        FUN_002c31f0();
    return g_igIntArrayMetaField_metaObject[0];
}
