#include "dw4/reflected.h"
extern igMetaObject *g_igEmptyFunctionList_metaObject[4];
extern "C" {
void FUN_00188cb0(void);
igMetaObject *igEmptyFunctionList_GetMetaObject(void);
}
igMetaObject *igEmptyFunctionList_GetMetaObject(void)
{
    igMetaObject *g = g_igEmptyFunctionList_metaObject[0];
    bool t;
    if (!g || !(t = g->_validity & 4))
        FUN_00188cb0();
    return g_igEmptyFunctionList_metaObject[0];
}
