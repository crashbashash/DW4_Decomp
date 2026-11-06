#include "dw4/reflected.h"
extern igMetaObject *g_igCustomStateCollectionList_metaObject[4];
extern "C" {
void FUN_0014ef20(void);
igMetaObject *igCustomStateCollectionList_GetMetaObject(void);
}
igMetaObject *igCustomStateCollectionList_GetMetaObject(void)
{
    igMetaObject *g = g_igCustomStateCollectionList_metaObject[0];
    if (!g || ((g->_validity & 4) != 0) == false)
        FUN_0014ef20();
    return g_igCustomStateCollectionList_metaObject[0];
}
