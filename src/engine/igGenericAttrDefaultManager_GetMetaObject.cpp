#include "dw4/reflected.h"
extern igMetaObject *g_igGenericAttrDefaultManager_metaObject[4];
extern "C" {
void FUN_00137b80(void);
igMetaObject *igGenericAttrDefaultManager_GetMetaObject(void);
}
igMetaObject *igGenericAttrDefaultManager_GetMetaObject(void)
{
    igMetaObject *g = g_igGenericAttrDefaultManager_metaObject[0];
    if (!g || ((g->_validity & 4) != 0) == false)
        FUN_00137b80();
    return g_igGenericAttrDefaultManager_metaObject[0];
}
