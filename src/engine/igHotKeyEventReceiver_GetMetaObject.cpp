#include "dw4/reflected.h"
extern igMetaObject *g_igHotKeyEventReceiver_metaObject[4];
extern "C" {
void igHotKeyEventReceiver_RunStaticInit(void);
igMetaObject *igHotKeyEventReceiver_GetMetaObject(void);
}
igMetaObject *igHotKeyEventReceiver_GetMetaObject(void)
{
    igMetaObject *g = g_igHotKeyEventReceiver_metaObject[0];
    if (!g || ((g->_validity & 4) != 0) == false)
        igHotKeyEventReceiver_RunStaticInit();
    return g_igHotKeyEventReceiver_metaObject[0];
}
