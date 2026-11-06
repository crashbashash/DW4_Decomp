#include "dw4/reflected.h"
extern igMetaObject *g_igSkeletonList_metaObject[4];
extern "C" {
void FUN_001984c0(void);
igMetaObject *igSkeletonList_GetMetaObject(void);
}
igMetaObject *igSkeletonList_GetMetaObject(void)
{
    igMetaObject *g = g_igSkeletonList_metaObject[0];
    bool t;
    if (!g || !(t = g->_validity & 4))
        FUN_001984c0();
    return g_igSkeletonList_metaObject[0];
}
