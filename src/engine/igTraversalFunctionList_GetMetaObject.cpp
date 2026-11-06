#include "dw4/reflected.h"
extern igMetaObject *g_igTraversalFunctionList_metaObject[4];
extern "C" {
void FUN_0019a800(void);
igMetaObject *igTraversalFunctionList_GetMetaObject(void);
}
igMetaObject *igTraversalFunctionList_GetMetaObject(void)
{
    igMetaObject *g = g_igTraversalFunctionList_metaObject[0];
    bool t;
    if (!g || !(t = g->_validity & 4))
        FUN_0019a800();
    return g_igTraversalFunctionList_metaObject[0];
}
