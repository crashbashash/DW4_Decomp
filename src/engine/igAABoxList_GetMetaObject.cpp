#include "dw4/reflected.h"
extern igMetaObject *g_igAABoxList_metaObject[4];
extern "C" {
void FUN_0018a5d0(void);
igMetaObject *igAABoxList_GetMetaObject(void);
}
igMetaObject *igAABoxList_GetMetaObject(void)
{
    igMetaObject *g = g_igAABoxList_metaObject[0];
    bool t;
    if (!g || !(t = g->_validity & 4))
        FUN_0018a5d0();
    return g_igAABoxList_metaObject[0];
}
