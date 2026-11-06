#include "dw4/reflected.h"
extern igMetaObject *g_igGetCenterFunctionList_metaObject[4];
extern "C" {
void FUN_001889f0(void);
igMetaObject *igGetCenterFunctionList_GetMetaObject(void);
}
igMetaObject *igGetCenterFunctionList_GetMetaObject(void)
{
    igMetaObject *g = g_igGetCenterFunctionList_metaObject[0];
    bool t;
    if (!g || !(t = g->_validity & 4))
        FUN_001889f0();
    return g_igGetCenterFunctionList_metaObject[0];
}
