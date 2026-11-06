#include "dw4/reflected.h"
extern igMetaObject *g_igAnimationCombinerBoneInfo_metaObject[4];
extern "C" {
void FUN_001a8220(void);
igMetaObject *igAnimationCombinerBoneInfo_GetMetaObject(void);
}
igMetaObject *igAnimationCombinerBoneInfo_GetMetaObject(void)
{
    igMetaObject *g = g_igAnimationCombinerBoneInfo_metaObject[0];
    bool t;
    if (!g || !(t = g->_validity & 4))
        FUN_001a8220();
    return g_igAnimationCombinerBoneInfo_metaObject[0];
}
