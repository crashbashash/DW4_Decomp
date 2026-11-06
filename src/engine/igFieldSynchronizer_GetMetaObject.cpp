#include "dw4/reflected.h"
extern igMetaObject *g_igFieldSynchronizer_metaObject[4];
extern "C" {
void igFieldSynchronizer_EnsureRegistered(void);
igMetaObject *igFieldSynchronizer_GetMetaObject(void);
}
igMetaObject *igFieldSynchronizer_GetMetaObject(void)
{
    igMetaObject *g = g_igFieldSynchronizer_metaObject[0];
    if (!g || ((g->_validity & 4) != 0) == false)
        igFieldSynchronizer_EnsureRegistered();
    return g_igFieldSynchronizer_metaObject[0];
}
