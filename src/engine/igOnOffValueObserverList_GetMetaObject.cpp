#include "dw4/reflected.h"
extern igMetaObject *g_igOnOffValueObserverList_metaObject[4];
extern "C" {
void igOnOffValueObserverList_EnsureRegistered(void);
igMetaObject *igOnOffValueObserverList_GetMetaObject(void);
}
igMetaObject *igOnOffValueObserverList_GetMetaObject(void)
{
    igMetaObject *g = g_igOnOffValueObserverList_metaObject[0];
    bool t;
    if (!g || !(t = g->_validity & 4))
        igOnOffValueObserverList_EnsureRegistered();
    return g_igOnOffValueObserverList_metaObject[0];
}
