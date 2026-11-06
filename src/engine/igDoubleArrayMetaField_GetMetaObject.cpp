#include "dw4/reflected.h"
extern igMetaObject *g_igDoubleArrayMetaField_metaObject[4];
extern "C" {
void FUN_002c6f40(void);
igMetaObject *igDoubleArrayMetaField_GetMetaObject(void);
}
igMetaObject *igDoubleArrayMetaField_GetMetaObject(void)
{
    igMetaObject *g = g_igDoubleArrayMetaField_metaObject[0];
    bool t;
    if (!g || !(t = g->_validity & 4))
        FUN_002c6f40();
    return g_igDoubleArrayMetaField_metaObject[0];
}
