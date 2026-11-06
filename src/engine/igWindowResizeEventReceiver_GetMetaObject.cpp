#include "dw4/reflected.h"
extern igMetaObject *g_igWindowResizeEventReceiver_metaObject[4];
extern "C" {
void FUN_00233160(void);
igMetaObject *igWindowResizeEventReceiver_GetMetaObject(void);
}
igMetaObject *igWindowResizeEventReceiver_GetMetaObject(void)
{
    igMetaObject *g = g_igWindowResizeEventReceiver_metaObject[0];
    bool t;
    if (!g || !(t = g->_validity & 4))
        FUN_00233160();
    return g_igWindowResizeEventReceiver_metaObject[0];
}
