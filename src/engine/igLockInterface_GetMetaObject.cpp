#include "dw4/reflected.h"
extern igMetaObject *g_igLockInterface_metaObject[4];
extern "C" {
void FUN_00226a10(void);
igMetaObject *igLockInterface_GetMetaObject(void);
}
igMetaObject *igLockInterface_GetMetaObject(void)
{
    igMetaObject *g = g_igLockInterface_metaObject[0];
    if (!g || ((g->_validity & 4) != 0) == false)
        FUN_00226a10();
    return g_igLockInterface_metaObject[0];
}
