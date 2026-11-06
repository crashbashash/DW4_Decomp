#include "dw4/reflected.h"
extern igMetaObject *g_igIntMetaField_metaObject[4];
extern "C" {
void igIntMetaField_EnsureRegistered(void);
igMetaObject *igIntMetaField_GetMetaObject(void);
}
igMetaObject *igIntMetaField_GetMetaObject(void)
{
    igMetaObject *g = g_igIntMetaField_metaObject[0];
    bool t;
    if (!g || !(t = g->_validity & 4))
        igIntMetaField_EnsureRegistered();
    return g_igIntMetaField_metaObject[0];
}
