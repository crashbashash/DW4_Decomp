#include "dw4/reflected.h"
extern igMetaObject *g_igAttrPool_metaObject[4];
extern "C" {
void FUN_0013a900(void);
igMetaObject *igAttrPool_GetMetaObject(void);
}
igMetaObject *igAttrPool_GetMetaObject(void)
{
    igMetaObject *g = g_igAttrPool_metaObject[0];
    if (!g || ((g->_validity & 4) != 0) == false)
        FUN_0013a900();
    return g_igAttrPool_metaObject[0];
}
