#include "dw4/reflected.h"
extern igMetaObject *g_igAttrSet_metaObject[4];
extern "C" {
void FUN_001a5e90(void);
igMetaObject *igAttrSet_GetMetaObject(void);
}
igMetaObject *igAttrSet_GetMetaObject(void)
{
    igMetaObject *g = g_igAttrSet_metaObject[0];
    bool t;
    if (!g || !(t = g->_validity & 4))
        FUN_001a5e90();
    return g_igAttrSet_metaObject[0];
}
