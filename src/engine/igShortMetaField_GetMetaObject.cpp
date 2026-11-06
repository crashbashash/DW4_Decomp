#include "dw4/reflected.h"
extern igMetaObject *g_igShortMetaField_metaObject[4];
extern "C" {
void igShortMetaField_EnsureRegistered(void);
igMetaObject *igShortMetaField_GetMetaObject(void);
}
igMetaObject *igShortMetaField_GetMetaObject(void)
{
    igMetaObject *g = g_igShortMetaField_metaObject[0];
    bool t;
    if (!g || !(t = g->_validity & 4))
        igShortMetaField_EnsureRegistered();
    return g_igShortMetaField_metaObject[0];
}
