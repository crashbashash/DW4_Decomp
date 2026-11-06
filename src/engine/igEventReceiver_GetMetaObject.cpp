#include "dw4/reflected.h"
extern igMetaObject *g_igEventReceiver_metaObject[4];
extern "C" {
void igEventReceiver_EnsureRegistered(void);
igMetaObject *igEventReceiver_GetMetaObject(void);
}
igMetaObject *igEventReceiver_GetMetaObject(void)
{
    igMetaObject *g = g_igEventReceiver_metaObject[0];
    if (!g || ((g->_validity & 4) != 0) == false)
        igEventReceiver_EnsureRegistered();
    return g_igEventReceiver_metaObject[0];
}
