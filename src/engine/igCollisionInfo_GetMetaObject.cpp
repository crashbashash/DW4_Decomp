#include "dw4/reflected.h"
extern igMetaObject *g_igCollisionInfo_metaObject[4];
extern "C" {
void FUN_00239910(void);
igMetaObject *igCollisionInfo_GetMetaObject(void);
}
igMetaObject *igCollisionInfo_GetMetaObject(void)
{
    igMetaObject *g = g_igCollisionInfo_metaObject[0];
    if (!g || ((g->_validity & 4) != 0) == false)
        FUN_00239910();
    return g_igCollisionInfo_metaObject[0];
}
