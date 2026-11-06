#include "dw4/reflected.h"
extern igMetaObject *g_igThreadList_metaObject[4];
extern "C" {
void FUN_002b8470(void);
igMetaObject *igThreadList_GetMetaObject(void);
}
igMetaObject *igThreadList_GetMetaObject(void)
{
    igMetaObject *g = g_igThreadList_metaObject[0];
    bool t;
    if (!g || !(t = g->_validity & 4))
        FUN_002b8470();
    return g_igThreadList_metaObject[0];
}
