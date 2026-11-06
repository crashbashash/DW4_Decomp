#include "dw4/reflected.h"
extern igMetaObject *g_igAnimationCombinerBoneInfoPool_metaObject[4];
extern "C" {
void igAnimationCombinerBoneInfoPool_RunStaticInit(void);
igMetaObject *igAnimationCombinerBoneInfoPool_GetMetaObject(void);
}
igMetaObject *igAnimationCombinerBoneInfoPool_GetMetaObject(void)
{
    igMetaObject *g = g_igAnimationCombinerBoneInfoPool_metaObject[0];
    if (!g || ((g->_validity & 4) != 0) == false)
        igAnimationCombinerBoneInfoPool_RunStaticInit();
    return g_igAnimationCombinerBoneInfoPool_metaObject[0];
}
