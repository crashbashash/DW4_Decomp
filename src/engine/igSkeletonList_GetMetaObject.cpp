#include "dw4/reflected.h"
extern igMetaObject *g_igSkeletonList_metaObject[4];
extern "C" {
void FUN_001984c0(void);
igMetaObject *igSkeletonList_GetMetaObject(void);
}
igMetaObject *igSkeletonList_GetMetaObject(void)
{
    igMetaObject *g = g_igSkeletonList_metaObject[0];
    if (!g || ((g->_validity & 4) != 0) == false)
        FUN_001984c0();
    return g_igSkeletonList_metaObject[0];
}
