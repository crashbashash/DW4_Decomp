#include "dw4/reflected.h"
extern igMetaObject *g_igShortArrayMetaField_metaObject[4];
extern "C" {
void FUN_002ba440(void);
igMetaObject *igShortArrayMetaField_GetMetaObject(void);
}
igMetaObject *igShortArrayMetaField_GetMetaObject(void)
{
    igMetaObject *g = g_igShortArrayMetaField_metaObject[0];
    bool t;
    if (!g || !(t = g->_validity & 4))
        FUN_002ba440();
    return g_igShortArrayMetaField_metaObject[0];
}
