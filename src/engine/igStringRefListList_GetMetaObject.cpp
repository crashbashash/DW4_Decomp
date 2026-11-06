#include "dw4/reflected.h"
extern igMetaObject *g_igStringRefListList_metaObject[4];
extern "C" {
void FUN_002c8780(void);
igMetaObject *igStringRefListList_GetMetaObject(void);
}
igMetaObject *igStringRefListList_GetMetaObject(void)
{
    igMetaObject *g = g_igStringRefListList_metaObject[0];
    bool t;
    if (!g || !(t = g->_validity & 4))
        FUN_002c8780();
    return g_igStringRefListList_metaObject[0];
}
