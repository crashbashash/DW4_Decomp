#include "dw4/reflected.h"
extern igMetaObject *g_igMessageReceiver_metaObject[4];
extern "C" {
void FUN_00231950(void);
igMetaObject *igMessageReceiver_GetMetaObject(void);
}
igMetaObject *igMessageReceiver_GetMetaObject(void)
{
    igMetaObject *g = g_igMessageReceiver_metaObject[0];
    if (!g || ((g->_validity & 4) != 0) == false)
        FUN_00231950();
    return g_igMessageReceiver_metaObject[0];
}
