#include "dw4/reflected.h"
extern igMetaObject *g_igPointerListList_metaObject[4];
extern "C" {
void FUN_002c90a0(void);
igMetaObject *igPointerListList_GetMetaObject(void);
}
igMetaObject *igPointerListList_GetMetaObject(void)
{
    igMetaObject *g = g_igPointerListList_metaObject[0];
    bool t;
    if (!g || !(t = g->_validity & 4))
        FUN_002c90a0();
    return g_igPointerListList_metaObject[0];
}
