#include "dw4/reflected.h"
extern igMetaObject *g_igSkeletonBoneInfoList_metaObject[4];
extern "C" {
void FUN_001988d0(void);
igMetaObject *igSkeletonBoneInfoList_GetMetaObject(void);
}
igMetaObject *igSkeletonBoneInfoList_GetMetaObject(void)
{
    igMetaObject *g = g_igSkeletonBoneInfoList_metaObject[0];
    if (!g || ((g->_validity & 4) != 0) == false)
        FUN_001988d0();
    return g_igSkeletonBoneInfoList_metaObject[0];
}
