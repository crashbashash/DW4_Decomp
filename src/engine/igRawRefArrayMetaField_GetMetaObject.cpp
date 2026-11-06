#include "dw4/reflected.h"
extern igMetaObject *g_igRawRefArrayMetaField_metaObject[4];
extern "C" {
void FUN_002bbec0(void);
igMetaObject *igRawRefArrayMetaField_GetMetaObject(void);
}
igMetaObject *igRawRefArrayMetaField_GetMetaObject(void)
{
    igMetaObject *g = g_igRawRefArrayMetaField_metaObject[0];
    bool t;
    if (!g || !(t = g->_validity & 4))
        FUN_002bbec0();
    return g_igRawRefArrayMetaField_metaObject[0];
}
