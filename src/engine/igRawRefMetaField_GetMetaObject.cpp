#include "dw4/reflected.h"
extern igMetaObject *g_igRawRefMetaField_metaObject[4];
extern "C" {
void igRawRefMetaField_EnsureRegistered(void);
igMetaObject *igRawRefMetaField_GetMetaObject(void);
}
igMetaObject *igRawRefMetaField_GetMetaObject(void)
{
    igMetaObject *g = g_igRawRefMetaField_metaObject[0];
    bool t;
    if (!g || !(t = g->_validity & 4))
        igRawRefMetaField_EnsureRegistered();
    return g_igRawRefMetaField_metaObject[0];
}
