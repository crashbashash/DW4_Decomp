#include "dw4/reflected.h"
extern igMetaObject *g_igRadioGroupSelectedObserver_metaObject[4];
extern "C" {
void igRadioGroupSelectedObserver_EnsureRegistered(void);
igMetaObject *igRadioGroupSelectedObserver_GetMetaObject(void);
}
igMetaObject *igRadioGroupSelectedObserver_GetMetaObject(void)
{
    igMetaObject *g = g_igRadioGroupSelectedObserver_metaObject[0];
    bool t;
    if (!g || !(t = g->_validity & 4))
        igRadioGroupSelectedObserver_EnsureRegistered();
    return g_igRadioGroupSelectedObserver_metaObject[0];
}
