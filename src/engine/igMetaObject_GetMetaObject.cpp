#include "dw4/reflected.h"
extern igMetaObject *g_igMetaObject_metaObject[4];
extern "C" {
void igMetaObject_EnsureRegistered(void);
igMetaObject *igMetaObject_GetMetaObject(void);
}
igMetaObject *igMetaObject_GetMetaObject(void)
{
    igMetaObject *g = g_igMetaObject_metaObject[0];
    bool t;
    if (!g || !(t = g->_validity & 4))
        igMetaObject_EnsureRegistered();
    return g_igMetaObject_metaObject[0];
}
