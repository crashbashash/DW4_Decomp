#include "dw4/reflected.h"
extern igMetaObject *g_igTransformFunctionList_metaObject[4];
extern "C" {
void FUN_00188e10(void);
igMetaObject *igTransformFunctionList_GetMetaObject(void);
}
igMetaObject *igTransformFunctionList_GetMetaObject(void)
{
    igMetaObject *g = g_igTransformFunctionList_metaObject[0];
    bool t;
    if (!g || !(t = g->_validity & 4))
        FUN_00188e10();
    return g_igTransformFunctionList_metaObject[0];
}
