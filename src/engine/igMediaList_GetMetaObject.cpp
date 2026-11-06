#include "dw4/reflected.h"
extern igMetaObject *g_igMediaList_metaObject[4];
extern "C" {
void FUN_002c1650(void);
igMetaObject *igMediaList_GetMetaObject(void);
}
igMetaObject *igMediaList_GetMetaObject(void)
{
    igMetaObject *g = g_igMediaList_metaObject[0];
    bool t;
    if (!g || !(t = g->_validity & 4))
        FUN_002c1650();
    return g_igMediaList_metaObject[0];
}
