#include "dw4/reflected.h"
extern igMetaObject *g_igVec4fMetaField_metaObject[4];
extern "C" {
void FUN_001873c0(void);
igMetaObject *igVec4fMetaField_GetMetaObject(void);
}
igMetaObject *igVec4fMetaField_GetMetaObject(void)
{
    igMetaObject *g = g_igVec4fMetaField_metaObject[0];
    bool t;
    if (!g || !(t = g->_validity & 4))
        FUN_001873c0();
    return g_igVec4fMetaField_metaObject[0];
}
