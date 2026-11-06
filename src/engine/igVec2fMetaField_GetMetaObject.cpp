#include "dw4/reflected.h"
extern igMetaObject *g_igVec2fMetaField_metaObject[4];
extern "C" {
void FUN_00187c70(void);
igMetaObject *igVec2fMetaField_GetMetaObject(void);
}
igMetaObject *igVec2fMetaField_GetMetaObject(void)
{
    igMetaObject *g = g_igVec2fMetaField_metaObject[0];
    bool t;
    if (!g || !(t = g->_validity & 4))
        FUN_00187c70();
    return g_igVec2fMetaField_metaObject[0];
}
