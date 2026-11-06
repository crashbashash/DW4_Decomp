#include "dw4/reflected.h"
extern igMetaObject *g_igTimeAttrPool_metaObject[4];
extern "C" {
void FUN_0019a370(void);
igMetaObject *igTimeAttrPool_GetMetaObject(void);
}
igMetaObject *igTimeAttrPool_GetMetaObject(void)
{
    igMetaObject *g = g_igTimeAttrPool_metaObject[0];
    if (!g || ((g->_validity & 4) != 0) == false)
        FUN_0019a370();
    return g_igTimeAttrPool_metaObject[0];
}
