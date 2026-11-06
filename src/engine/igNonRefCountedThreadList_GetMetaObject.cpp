#include "dw4/reflected.h"
extern igMetaObject *g_igNonRefCountedThreadList_metaObject[4];
extern "C" {
void FUN_002b8300(void);
igMetaObject *igNonRefCountedThreadList_GetMetaObject(void);
}
igMetaObject *igNonRefCountedThreadList_GetMetaObject(void)
{
    igMetaObject *g = g_igNonRefCountedThreadList_metaObject[0];
    bool t;
    if (!g || !(t = g->_validity & 4))
        FUN_002b8300();
    return g_igNonRefCountedThreadList_metaObject[0];
}
