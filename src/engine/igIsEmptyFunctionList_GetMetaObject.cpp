#include "dw4/reflected.h"
extern igMetaObject *g_igIsEmptyFunctionList_metaObject[4];
extern "C" {
void FUN_00188b50(void);
igMetaObject *igIsEmptyFunctionList_GetMetaObject(void);
}
igMetaObject *igIsEmptyFunctionList_GetMetaObject(void)
{
    igMetaObject *g = g_igIsEmptyFunctionList_metaObject[0];
    if (!g || ((g->_validity & 4) != 0) == false)
        FUN_00188b50();
    return g_igIsEmptyFunctionList_metaObject[0];
}
