#include "dw4/reflected.h"
extern igMetaObject *g_igNonRefCountedNodeList_metaObject[4];
extern "C" {
void FUN_0019c9a0(void);
igMetaObject *igNonRefCountedNodeList_GetMetaObject(void);
}
igMetaObject *igNonRefCountedNodeList_GetMetaObject(void)
{
    igMetaObject *g = g_igNonRefCountedNodeList_metaObject[0];
    bool t;
    if (!g || !(t = g->_validity & 4))
        FUN_0019c9a0();
    return g_igNonRefCountedNodeList_metaObject[0];
}
