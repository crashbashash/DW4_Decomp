#include "dw4/reflected.h"
extern igMetaObject *g_igContainsRayFunctionList_metaObject[4];
extern "C" {
void FUN_00189230(void);
igMetaObject *igContainsRayFunctionList_GetMetaObject(void);
}
igMetaObject *igContainsRayFunctionList_GetMetaObject(void)
{
    igMetaObject *g = g_igContainsRayFunctionList_metaObject[0];
    bool t;
    if (!g || !(t = g->_validity & 4))
        FUN_00189230();
    return g_igContainsRayFunctionList_metaObject[0];
}
