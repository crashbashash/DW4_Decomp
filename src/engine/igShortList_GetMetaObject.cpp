#include "dw4/reflected.h"
extern igMetaObject *g_igShortList_metaObject[4];
extern "C" {
void FUN_002c9ea0(void);
igMetaObject *igShortList_GetMetaObject(void);
}
igMetaObject *igShortList_GetMetaObject(void)
{
    igMetaObject *g = g_igShortList_metaObject[0];
    bool t;
    if (!g || !(t = g->_validity & 4))
        FUN_002c9ea0();
    return g_igShortList_metaObject[0];
}
