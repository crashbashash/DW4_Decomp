#include "dw4/reflected.h"
extern igMetaObject *g_igQuaternionfList_metaObject[4];
extern "C" {
void FUN_00189cf0(void);
igMetaObject *igQuaternionfList_GetMetaObject(void);
}
igMetaObject *igQuaternionfList_GetMetaObject(void)
{
    igMetaObject *g = g_igQuaternionfList_metaObject[0];
    if (!g || ((g->_validity & 4) != 0) == false)
        FUN_00189cf0();
    return g_igQuaternionfList_metaObject[0];
}
