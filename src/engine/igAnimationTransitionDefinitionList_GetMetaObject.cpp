#include "dw4/reflected.h"
extern igMetaObject *g_igAnimationTransitionDefinitionList_metaObject[4];
extern "C" {
void FUN_001a9500(void);
igMetaObject *igAnimationTransitionDefinitionList_GetMetaObject(void);
}
igMetaObject *igAnimationTransitionDefinitionList_GetMetaObject(void)
{
    igMetaObject *g = g_igAnimationTransitionDefinitionList_metaObject[0];
    if (!g || ((g->_validity & 4) != 0) == false)
        FUN_001a9500();
    return g_igAnimationTransitionDefinitionList_metaObject[0];
}
