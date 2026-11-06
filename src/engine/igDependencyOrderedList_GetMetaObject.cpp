#include "dw4/reflected.h"
extern igMetaObject *g_igDependencyOrderedList_metaObject[4];
extern "C" {
void FUN_002c7ba0(void);
igMetaObject *igDependencyOrderedList_GetMetaObject(void);
}
igMetaObject *igDependencyOrderedList_GetMetaObject(void)
{
    igMetaObject *g = g_igDependencyOrderedList_metaObject[0];
    if (!g || ((g->_validity & 4) != 0) == false)
        FUN_002c7ba0();
    return g_igDependencyOrderedList_metaObject[0];
}
