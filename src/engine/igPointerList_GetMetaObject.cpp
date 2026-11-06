#include "dw4/reflected.h"
extern igMetaObject *g_igPointerList_metaObject[4];
extern "C" {
void FUN_002c9250(void);
igMetaObject *igPointerList_GetMetaObject(void);
}
igMetaObject *igPointerList_GetMetaObject(void)
{
    igMetaObject *g = g_igPointerList_metaObject[0];
    bool t;
    if (!g || !(t = g->_validity & 4))
        FUN_002c9250();
    return g_igPointerList_metaObject[0];
}
