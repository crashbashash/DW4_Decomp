#include "dw4/reflected.h"
extern igMetaObject *g_igNodeListList_metaObject[4];
extern "C" {
void FUN_0019cb10(void);
igMetaObject *igNodeListList_GetMetaObject(void);
}
igMetaObject *igNodeListList_GetMetaObject(void)
{
    igMetaObject *g = g_igNodeListList_metaObject[0];
    if (!g || ((g->_validity & 4) != 0) == false)
        FUN_0019cb10();
    return g_igNodeListList_metaObject[0];
}
