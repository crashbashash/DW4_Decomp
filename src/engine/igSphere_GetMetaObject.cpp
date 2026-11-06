#include "dw4/reflected.h"
extern igMetaObject *g_igSphere_metaObject[4];
extern "C" {
void FUN_00187f30(void);
igMetaObject *igSphere_GetMetaObject(void);
}
igMetaObject *igSphere_GetMetaObject(void)
{
    igMetaObject *g = g_igSphere_metaObject[0];
    if (!g || ((g->_validity & 4) != 0) == false)
        FUN_00187f30();
    return g_igSphere_metaObject[0];
}
