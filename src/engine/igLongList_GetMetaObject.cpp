#include "dw4/reflected.h"
extern igMetaObject *g_igLongList_metaObject[4];
extern "C" {
void FUN_002ca760(void);
igMetaObject *igLongList_GetMetaObject(void);
}
igMetaObject *igLongList_GetMetaObject(void)
{
    igMetaObject *g = g_igLongList_metaObject[0];
    bool t;
    if (!g || !(t = g->_validity & 4))
        FUN_002ca760();
    return g_igLongList_metaObject[0];
}
