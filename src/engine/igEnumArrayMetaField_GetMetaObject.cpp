#include "dw4/reflected.h"
extern igMetaObject *g_igEnumArrayMetaField_metaObject[4];
extern "C" {
void FUN_002c64e0(void);
igMetaObject *igEnumArrayMetaField_GetMetaObject(void);
}
igMetaObject *igEnumArrayMetaField_GetMetaObject(void)
{
    igMetaObject *g = g_igEnumArrayMetaField_metaObject[0];
    bool t;
    if (!g || !(t = g->_validity & 4))
        FUN_002c64e0();
    return g_igEnumArrayMetaField_metaObject[0];
}
