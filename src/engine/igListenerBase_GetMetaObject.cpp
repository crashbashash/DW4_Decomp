#include "dw4/reflected.h"
extern igMetaObject *g_igListenerBase_metaObject[4];
extern "C" {
void FUN_002272f0(void);
igMetaObject *igListenerBase_GetMetaObject(void);
}
igMetaObject *igListenerBase_GetMetaObject(void)
{
    igMetaObject *g = g_igListenerBase_metaObject[0];
    bool t;
    if (!g || !(t = g->_validity & 4))
        FUN_002272f0();
    return g_igListenerBase_metaObject[0];
}
