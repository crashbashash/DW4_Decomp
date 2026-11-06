#include "dw4/reflected.h"
extern igMetaObject *g_igNamedObjectList_metaObject[4];
extern "C" {
void FUN_002be1e0(void);
igMetaObject *igNamedObjectList_GetMetaObject(void);
}
igMetaObject *igNamedObjectList_GetMetaObject(void)
{
    igMetaObject *g = g_igNamedObjectList_metaObject[0];
    bool t;
    if (!g || !(t = g->_validity & 4))
        FUN_002be1e0();
    return g_igNamedObjectList_metaObject[0];
}
