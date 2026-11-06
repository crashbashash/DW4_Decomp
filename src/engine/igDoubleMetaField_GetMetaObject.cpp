#include "dw4/reflected.h"
extern igMetaObject *g_igDoubleMetaField_metaObject[4];
extern "C" {
void FUN_002c6cc0(void);
igMetaObject *igDoubleMetaField_GetMetaObject(void);
}
igMetaObject *igDoubleMetaField_GetMetaObject(void)
{
    igMetaObject *g = g_igDoubleMetaField_metaObject[0];
    bool t;
    if (!g || !(t = g->_validity & 4))
        FUN_002c6cc0();
    return g_igDoubleMetaField_metaObject[0];
}
