#include "dw4/reflected.h"
extern igMetaObject *g_igAnimationTransitionDefinition_metaObject[4];
extern "C" {
void FUN_001a96c0(void);
igMetaObject *igAnimationTransitionDefinition_GetMetaObject(void);
}
igMetaObject *igAnimationTransitionDefinition_GetMetaObject(void)
{
    igMetaObject *g = g_igAnimationTransitionDefinition_metaObject[0];
    bool t;
    if (!g || !(t = g->_validity & 4))
        FUN_001a96c0();
    return g_igAnimationTransitionDefinition_metaObject[0];
}
