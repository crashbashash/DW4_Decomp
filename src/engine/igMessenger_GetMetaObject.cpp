#include "dw4/reflected.h"
extern igMetaObject *g_igMessenger_metaObject[4];
extern "C" {
void FUN_00231530(void);
igMetaObject *igMessenger_GetMetaObject(void);
}
igMetaObject *igMessenger_GetMetaObject(void)
{
    igMetaObject *g = g_igMessenger_metaObject[0];
    bool t;
    if (!g || !(t = g->_validity & 4))
        FUN_00231530();
    return g_igMessenger_metaObject[0];
}
