#include "dw4/reflected.h"
extern igMetaObject *g_igMessageDispatcher_metaObject[4];
extern "C" {
void FUN_00232150(void);
igMetaObject *igMessageDispatcher_GetMetaObject(void);
}
igMetaObject *igMessageDispatcher_GetMetaObject(void)
{
    igMetaObject *g = g_igMessageDispatcher_metaObject[0];
    bool t;
    if (!g || !(t = g->_validity & 4))
        FUN_00232150();
    return g_igMessageDispatcher_metaObject[0];
}
