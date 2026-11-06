#include "dw4/reflected.h"
extern igMetaObject *g_igAttrDefaultManager_metaObject[4];
extern "C" {
void FUN_0013ab50(void);
igMetaObject *igAttrDefaultManager_GetMetaObject(void);
}
igMetaObject *igAttrDefaultManager_GetMetaObject(void)
{
    igMetaObject *g = g_igAttrDefaultManager_metaObject[0];
    bool t;
    if (!g || !(t = g->_validity & 4))
        FUN_0013ab50();
    return g_igAttrDefaultManager_metaObject[0];
}
