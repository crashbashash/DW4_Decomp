#include "dw4/reflected.h"
extern igMetaObject *g_igDependencyList_metaObject[4];
extern "C" {
void FUN_002c7e20(void);
igMetaObject *igDependencyList_GetMetaObject(void);
}
igMetaObject *igDependencyList_GetMetaObject(void)
{
    igMetaObject *g = g_igDependencyList_metaObject[0];
    if (!g || ((g->_validity & 4) != 0) == false)
        FUN_002c7e20();
    return g_igDependencyList_metaObject[0];
}
