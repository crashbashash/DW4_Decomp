#include "dw4/reflected.h"
extern igMetaObject *g_igExtendByFunctionList_metaObject[4];
extern "C" {
void FUN_001897b0(void);
igMetaObject *igExtendByFunctionList_GetMetaObject(void);
}
igMetaObject *igExtendByFunctionList_GetMetaObject(void)
{
    igMetaObject *g = g_igExtendByFunctionList_metaObject[0];
    bool t;
    if (!g || !(t = g->_validity & 4))
        FUN_001897b0();
    return g_igExtendByFunctionList_metaObject[0];
}
