#include "dw4/reflected.h"
extern igMetaObject *g_igAnimationCombinerBoneInfoListList_metaObject[4];
extern "C" {
void FUN_001a7f00(void);
igMetaObject *igAnimationCombinerBoneInfoListList_GetMetaObject(void);
}
igMetaObject *igAnimationCombinerBoneInfoListList_GetMetaObject(void)
{
    igMetaObject *g = g_igAnimationCombinerBoneInfoListList_metaObject[0];
    if (!g || ((g->_validity & 4) != 0) == false)
        FUN_001a7f00();
    return g_igAnimationCombinerBoneInfoListList_metaObject[0];
}
