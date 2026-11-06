#include "dw4/reflected.h"
extern igMetaObject *g_igCollisionGrid_metaObject[4];
extern "C" {
void FUN_0023a340(void);
igMetaObject *igCollisionGrid_GetMetaObject(void);
}
igMetaObject *igCollisionGrid_GetMetaObject(void)
{
    igMetaObject *g = g_igCollisionGrid_metaObject[0];
    if (!g || ((g->_validity & 4) != 0) == false)
        FUN_0023a340();
    return g_igCollisionGrid_metaObject[0];
}
