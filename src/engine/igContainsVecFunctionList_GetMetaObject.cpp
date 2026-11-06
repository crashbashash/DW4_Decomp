#include "dw4/reflected.h"
extern igMetaObject *g_igContainsVecFunctionList_metaObject[4];
extern "C" {
void FUN_00188f70(void);
igMetaObject *igContainsVecFunctionList_GetMetaObject(void);
}
igMetaObject *igContainsVecFunctionList_GetMetaObject(void)
{
    igMetaObject *g = g_igContainsVecFunctionList_metaObject[0];
    if (!g || ((g->_validity & 4) != 0) == false)
        FUN_00188f70();
    return g_igContainsVecFunctionList_metaObject[0];
}
