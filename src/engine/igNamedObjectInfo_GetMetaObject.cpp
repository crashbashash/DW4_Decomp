#include "dw4/reflected.h"
extern igMetaObject *g_igNamedObjectInfo_metaObject[4];
extern "C" {
void FUN_002bdfc0(void);
igMetaObject *igNamedObjectInfo_GetMetaObject(void);
}
igMetaObject *igNamedObjectInfo_GetMetaObject(void)
{
    igMetaObject *g = g_igNamedObjectInfo_metaObject[0];
    bool t;
    if (!g || !(t = g->_validity & 4))
        FUN_002bdfc0();
    return g_igNamedObjectInfo_metaObject[0];
}
