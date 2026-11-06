#include "dw4/reflected.h"
extern igMetaObject *g_igMessageFilterList_metaObject[4];
extern "C" {
void FUN_00231ab0(void);
igMetaObject *igMessageFilterList_GetMetaObject(void);
}
igMetaObject *igMessageFilterList_GetMetaObject(void)
{
    igMetaObject *g = g_igMessageFilterList_metaObject[0];
    bool t;
    if (!g || !(t = g->_validity & 4))
        FUN_00231ab0();
    return g_igMessageFilterList_metaObject[0];
}
