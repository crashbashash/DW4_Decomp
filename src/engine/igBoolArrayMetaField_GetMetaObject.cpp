#include "dw4/reflected.h"
extern igMetaObject *g_igBoolArrayMetaField_metaObject[4];
extern "C" {
void FUN_002ccf60(void);
igMetaObject *igBoolArrayMetaField_GetMetaObject(void);
}
igMetaObject *igBoolArrayMetaField_GetMetaObject(void)
{
    igMetaObject *g = g_igBoolArrayMetaField_metaObject[0];
    bool t;
    if (!g || !(t = g->_validity & 4))
        FUN_002ccf60();
    return g_igBoolArrayMetaField_metaObject[0];
}
