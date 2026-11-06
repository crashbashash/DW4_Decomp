#include "dw4/reflected.h"
extern igMetaObject *g_igBoolMetaField_metaObject[4];
extern "C" {
void FUN_002ccca0(void);
igMetaObject *igBoolMetaField_GetMetaObject(void);
}
igMetaObject *igBoolMetaField_GetMetaObject(void)
{
    igMetaObject *g = g_igBoolMetaField_metaObject[0];
    bool t;
    if (!g || !(t = g->_validity & 4))
        FUN_002ccca0();
    return g_igBoolMetaField_metaObject[0];
}
