#include "dw4/reflected.h"
extern igMetaObject *g_igOnOffValueObserver_metaObject[4];
extern "C" {
void igOnOffValueObserver_EnsureRegistered(void);
igMetaObject *igOnOffValueObserver_GetMetaObject(void);
}
igMetaObject *igOnOffValueObserver_GetMetaObject(void)
{
    igMetaObject *g = g_igOnOffValueObserver_metaObject[0];
    if (!g || ((g->_validity & 4) != 0) == false)
        igOnOffValueObserver_EnsureRegistered();
    return g_igOnOffValueObserver_metaObject[0];
}
