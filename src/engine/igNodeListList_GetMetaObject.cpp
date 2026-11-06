#include "dw4/reflected.h"
extern igMetaObject *g_igNodeListList_metaObject[4];
extern "C" {
void FUN_0019cb10(void);
igMetaObject *igNodeListList_GetMetaObject(void);
}
igMetaObject *igNodeListList_GetMetaObject(void)
{
    igMetaObject *g = g_igNodeListList_metaObject[0];
    bool t;
    if (!g || !(t = g->_validity & 4))
        FUN_0019cb10();
    return g_igNodeListList_metaObject[0];
}
