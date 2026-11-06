#include "dw4/reflected.h"
extern igMetaObject *g_igFloatArrayMetaField_metaObject[4];
extern "C" {
void FUN_002c49d0(void);
igMetaObject *igFloatArrayMetaField_GetMetaObject(void);
}
igMetaObject *igFloatArrayMetaField_GetMetaObject(void)
{
    igMetaObject *g = g_igFloatArrayMetaField_metaObject[0];
    bool t;
    if (!g || !(t = g->_validity & 4))
        FUN_002c49d0();
    return g_igFloatArrayMetaField_metaObject[0];
}
