#include "dw4/reflected.h"
extern igMetaObject *g_igCollisionGroup_metaObject[4];
extern "C" {
void FUN_00239c80(void);
igMetaObject *igCollisionGroup_GetMetaObject(void);
}
igMetaObject *igCollisionGroup_GetMetaObject(void)
{
    igMetaObject *g = g_igCollisionGroup_metaObject[0];
    if (!g || ((g->_validity & 4) != 0) == false)
        FUN_00239c80();
    return g_igCollisionGroup_metaObject[0];
}
