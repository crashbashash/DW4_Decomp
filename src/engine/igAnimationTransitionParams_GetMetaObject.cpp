#include "dw4/reflected.h"
extern igMetaObject *g_igAnimationTransitionParams_metaObject[4];
extern "C" {
void FUN_001a9c90(void);
igMetaObject *igAnimationTransitionParams_GetMetaObject(void);
}
igMetaObject *igAnimationTransitionParams_GetMetaObject(void)
{
    igMetaObject *g = g_igAnimationTransitionParams_metaObject[0];
    if (!g || ((g->_validity & 4) != 0) == false)
        FUN_001a9c90();
    return g_igAnimationTransitionParams_metaObject[0];
}
