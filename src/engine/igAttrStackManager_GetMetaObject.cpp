#include "dw4/reflected.h"
extern igMetaObject *g_igAttrStackManager_metaObject[4];
extern "C" {
void FUN_001a5640(void);
igMetaObject *igAttrStackManager_GetMetaObject(void);
}
igMetaObject *igAttrStackManager_GetMetaObject(void)
{
    igMetaObject *g = g_igAttrStackManager_metaObject[0];
    bool t;
    if (!g || !(t = g->_validity & 4))
        FUN_001a5640();
    return g_igAttrStackManager_metaObject[0];
}
