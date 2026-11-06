#include "dw4/reflected.h"
extern igMetaObject *g_igGroup_metaObject[4];
extern "C" {
void FUN_0019f330(void);
igMetaObject *igGroup_GetMetaObject(void);
}
igMetaObject *igGroup_GetMetaObject(void)
{
    igMetaObject *g = g_igGroup_metaObject[0];
    if (!g || ((g->_validity & 4) != 0) == false)
        FUN_0019f330();
    return g_igGroup_metaObject[0];
}
