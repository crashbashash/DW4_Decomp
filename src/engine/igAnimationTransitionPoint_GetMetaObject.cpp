#include "dw4/reflected.h"
extern igMetaObject *g_igAnimationTransitionPoint_metaObject[4];
extern "C" {
void FUN_001a9a80(void);
igMetaObject *igAnimationTransitionPoint_GetMetaObject(void);
}
igMetaObject *igAnimationTransitionPoint_GetMetaObject(void)
{
    igMetaObject *g = g_igAnimationTransitionPoint_metaObject[0];
    bool t;
    if (!g || !(t = g->_validity & 4))
        FUN_001a9a80();
    return g_igAnimationTransitionPoint_metaObject[0];
}
