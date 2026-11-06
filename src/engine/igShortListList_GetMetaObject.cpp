#include "dw4/reflected.h"
extern igMetaObject *g_igShortListList_metaObject[4];
extern "C" {
void FUN_002c9cf0(void);
igMetaObject *igShortListList_GetMetaObject(void);
}
igMetaObject *igShortListList_GetMetaObject(void)
{
    igMetaObject *g = g_igShortListList_metaObject[0];
    bool t;
    if (!g || !(t = g->_validity & 4))
        FUN_002c9cf0();
    return g_igShortListList_metaObject[0];
}
