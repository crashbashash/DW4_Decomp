#include "dw4/reflected.h"
extern igMetaObject *g_igVirtualCFuncMetaField_metaObject[4];
extern "C" {
void FUN_002b5e80(void);
igMetaObject *igVirtualCFuncMetaField_GetMetaObject(void);
}
igMetaObject *igVirtualCFuncMetaField_GetMetaObject(void)
{
    igMetaObject *g = g_igVirtualCFuncMetaField_metaObject[0];
    bool t;
    if (!g || !(t = g->_validity & 4))
        FUN_002b5e80();
    return g_igVirtualCFuncMetaField_metaObject[0];
}
