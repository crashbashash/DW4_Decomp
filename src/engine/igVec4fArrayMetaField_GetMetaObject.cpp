#include "dw4/reflected.h"
extern igMetaObject *g_igVec4fArrayMetaField_metaObject[4];
extern "C" {
void FUN_00187680(void);
igMetaObject *igVec4fArrayMetaField_GetMetaObject(void);
}
igMetaObject *igVec4fArrayMetaField_GetMetaObject(void)
{
    igMetaObject *g = g_igVec4fArrayMetaField_metaObject[0];
    bool t;
    if (!g || !(t = g->_validity & 4))
        FUN_00187680();
    return g_igVec4fArrayMetaField_metaObject[0];
}
