#include "dw4/reflected.h"
extern igMetaObject *g_igVec3fMetaField_metaObject[4];
extern "C" {
void FUN_001879b0(void);
igMetaObject *igVec3fMetaField_GetMetaObject(void);
}
igMetaObject *igVec3fMetaField_GetMetaObject(void)
{
    igMetaObject *g = g_igVec3fMetaField_metaObject[0];
    if (!g || ((g->_validity & 4) != 0) == false)
        FUN_001879b0();
    return g_igVec3fMetaField_metaObject[0];
}
