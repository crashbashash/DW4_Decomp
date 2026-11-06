#include "dw4/reflected.h"
extern igMetaObject *g_igNamedObject_metaObject[4];
extern "C" {
void FUN_002be3d0(void);
igMetaObject *igNamedObject_GetMetaObject(void);
}
igMetaObject *igNamedObject_GetMetaObject(void)
{
    igMetaObject *g = g_igNamedObject_metaObject[0];
    if (!g || ((g->_validity & 4) != 0) == false)
        FUN_002be3d0();
    return g_igNamedObject_metaObject[0];
}
