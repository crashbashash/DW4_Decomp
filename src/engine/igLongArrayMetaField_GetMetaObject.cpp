#include "dw4/reflected.h"
extern igMetaObject *g_igLongArrayMetaField_metaObject[4];
extern "C" {
void FUN_002c1d90(void);
igMetaObject *igLongArrayMetaField_GetMetaObject(void);
}
igMetaObject *igLongArrayMetaField_GetMetaObject(void)
{
    igMetaObject *g = g_igLongArrayMetaField_metaObject[0];
    bool t;
    if (!g || !(t = g->_validity & 4))
        FUN_002c1d90();
    return g_igLongArrayMetaField_metaObject[0];
}
