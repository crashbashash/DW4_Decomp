#include "dw4/reflected.h"
extern igMetaObject *g_igEventDispatcher_metaObject[4];
extern "C" {
void igEventDispatcher_EnsureRegistered(void);
igMetaObject *igEventDispatcher_GetMetaObject(void);
}
igMetaObject *igEventDispatcher_GetMetaObject(void)
{
    igMetaObject *g = g_igEventDispatcher_metaObject[0];
    bool t;
    if (!g || !(t = g->_validity & 4))
        igEventDispatcher_EnsureRegistered();
    return g_igEventDispatcher_metaObject[0];
}
