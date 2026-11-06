#include "dw4/reflected.h"
extern igMetaObject *g_igShortListList_metaObject[4];
extern "C" {
void FUN_002c9cf0(void);
igMetaObject *igShortListList_GetMetaObject(void);
}
igMetaObject *igShortListList_GetMetaObject(void)
{
    igMetaObject *g = g_igShortListList_metaObject[0];
    if (!g || ((g->_validity & 4) != 0) == false)
        FUN_002c9cf0();
    return g_igShortListList_metaObject[0];
}
