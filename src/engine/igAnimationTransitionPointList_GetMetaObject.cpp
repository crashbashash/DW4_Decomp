#include "dw4/reflected.h"
extern igMetaObject *g_igAnimationTransitionPointList_metaObject[4];
extern "C" {
void FUN_001a9910(void);
igMetaObject *igAnimationTransitionPointList_GetMetaObject(void);
}
igMetaObject *igAnimationTransitionPointList_GetMetaObject(void)
{
    igMetaObject *g = g_igAnimationTransitionPointList_metaObject[0];
    bool t;
    if (!g || !(t = g->_validity & 4))
        FUN_001a9910();
    return g_igAnimationTransitionPointList_metaObject[0];
}
