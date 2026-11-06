#include "dw4/reflected.h"
extern igMetaObject *g_igQuaternionfList_metaObject[4];
extern "C" {
void FUN_00189cf0(void);
igMetaObject *igQuaternionfList_GetMetaObject(void);
}
igMetaObject *igQuaternionfList_GetMetaObject(void)
{
    igMetaObject *g = g_igQuaternionfList_metaObject[0];
    bool t;
    if (!g || !(t = g->_validity & 4))
        FUN_00189cf0();
    return g_igQuaternionfList_metaObject[0];
}
