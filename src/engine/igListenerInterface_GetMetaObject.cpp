#include "dw4/reflected.h"
extern igMetaObject *g_igListenerInterface_metaObject[4];
extern "C" {
void FUN_00226e30(void);
igMetaObject *igListenerInterface_GetMetaObject(void);
}
igMetaObject *igListenerInterface_GetMetaObject(void)
{
    igMetaObject *g = g_igListenerInterface_metaObject[0];
    if (!g || ((g->_validity & 4) != 0) == false)
        FUN_00226e30();
    return g_igListenerInterface_metaObject[0];
}
