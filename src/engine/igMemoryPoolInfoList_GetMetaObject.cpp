#include "dw4/reflected.h"
extern igMetaObject *g_igMemoryPoolInfoList_metaObject[4];
extern "C" {
void FUN_002bfe40(void);
igMetaObject *igMemoryPoolInfoList_GetMetaObject(void);
}
igMetaObject *igMemoryPoolInfoList_GetMetaObject(void)
{
    igMetaObject *g = g_igMemoryPoolInfoList_metaObject[0];
    if (!g || ((g->_validity & 4) != 0) == false)
        FUN_002bfe40();
    return g_igMemoryPoolInfoList_metaObject[0];
}
