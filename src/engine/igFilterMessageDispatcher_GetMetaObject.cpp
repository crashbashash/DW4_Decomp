#include "dw4/reflected.h"
extern igMetaObject *g_igFilterMessageDispatcher_metaObject[4];
extern "C" {
void FUN_00231f40(void);
igMetaObject *igFilterMessageDispatcher_GetMetaObject(void);
}
igMetaObject *igFilterMessageDispatcher_GetMetaObject(void)
{
    igMetaObject *g = g_igFilterMessageDispatcher_metaObject[0];
    bool t;
    if (!g || !(t = g->_validity & 4))
        FUN_00231f40();
    return g_igFilterMessageDispatcher_metaObject[0];
}
