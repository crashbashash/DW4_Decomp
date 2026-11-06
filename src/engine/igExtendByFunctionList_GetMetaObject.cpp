#include "dw4/reflected.h"
extern igMetaObject *g_igExtendByFunctionList_metaObject[4];
extern "C" {
void FUN_001897b0(void);
igMetaObject *igExtendByFunctionList_GetMetaObject(void);
}
igMetaObject *igExtendByFunctionList_GetMetaObject(void)
{
    igMetaObject *g = g_igExtendByFunctionList_metaObject[0];
    if (!g || ((g->_validity & 4) != 0) == false)
        FUN_001897b0();
    return g_igExtendByFunctionList_metaObject[0];
}
