#include "dw4/reflected.h"
extern igMetaObject *g_igFieldSynchronizer_metaObject[4];
extern "C" {
void igFieldSynchronizer_EnsureRegistered(void);
igMetaObject *igFieldSynchronizer_GetMetaObject(void);
}
igMetaObject *igFieldSynchronizer_GetMetaObject(void)
{
    igMetaObject *g = g_igFieldSynchronizer_metaObject[0];
    bool t;
    if (!g || !(t = g->_validity & 4))
        igFieldSynchronizer_EnsureRegistered();
    return g_igFieldSynchronizer_metaObject[0];
}
