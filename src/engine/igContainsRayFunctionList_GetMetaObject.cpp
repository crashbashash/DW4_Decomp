#include "dw4/reflected.h"
extern igMetaObject *g_igContainsRayFunctionList_metaObject[4];
extern "C" {
void FUN_00189230(void);
igMetaObject *igContainsRayFunctionList_GetMetaObject(void);
}
igMetaObject *igContainsRayFunctionList_GetMetaObject(void)
{
    igMetaObject *g = g_igContainsRayFunctionList_metaObject[0];
    if (!g || ((g->_validity & 4) != 0) == false)
        FUN_00189230();
    return g_igContainsRayFunctionList_metaObject[0];
}
