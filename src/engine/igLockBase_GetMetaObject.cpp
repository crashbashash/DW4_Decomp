#include "dw4/reflected.h"
extern igMetaObject *g_igLockBase_metaObject[4];
extern "C" {
void FUN_00226be0(void);
igMetaObject *igLockBase_GetMetaObject(void);
}
igMetaObject *igLockBase_GetMetaObject(void)
{
    igMetaObject *g = g_igLockBase_metaObject[0];
    bool t;
    if (!g || !(t = g->_validity & 4))
        FUN_00226be0();
    return g_igLockBase_metaObject[0];
}
