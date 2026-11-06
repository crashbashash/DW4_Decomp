#include "dw4/reflected.h"
extern igMetaObject *g_igAnimationCombinerBoneInfoList_metaObject[4];
extern "C" {
void FUN_001a8020(void);
igMetaObject *igAnimationCombinerBoneInfoList_GetMetaObject(void);
}
igMetaObject *igAnimationCombinerBoneInfoList_GetMetaObject(void)
{
    igMetaObject *g = g_igAnimationCombinerBoneInfoList_metaObject[0];
    if (!g || ((g->_validity & 4) != 0) == false)
        FUN_001a8020();
    return g_igAnimationCombinerBoneInfoList_metaObject[0];
}
