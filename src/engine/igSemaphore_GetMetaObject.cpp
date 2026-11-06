#include "dw4/reflected.h"
extern igMetaObject *g_igSemaphore_metaObject[4];
extern "C" {
void FUN_002ba730(void);
igMetaObject *igSemaphore_GetMetaObject(void);
}
igMetaObject *igSemaphore_GetMetaObject(void)
{
    igMetaObject *g = g_igSemaphore_metaObject[0];
    bool t;
    if (!g || !(t = g->_validity & 4))
        FUN_002ba730();
    return g_igSemaphore_metaObject[0];
}
