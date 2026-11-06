#include "dw4/reflected.h"
extern igMetaObject *g_igExtendByVecFunctionList_metaObject[4];
extern "C" {
void FUN_001890d0(void);
igMetaObject *igExtendByVecFunctionList_GetMetaObject(void);
}
igMetaObject *igExtendByVecFunctionList_GetMetaObject(void)
{
    igMetaObject *g = g_igExtendByVecFunctionList_metaObject[0];
    bool t;
    if (!g || !(t = g->_validity & 4))
        FUN_001890d0();
    return g_igExtendByVecFunctionList_metaObject[0];
}
