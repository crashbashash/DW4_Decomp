#include "dw4/reflected.h"
extern igMetaObject *g_igAnimationHierarchy_metaObject[4];
extern "C" {
void FUN_001a71a0(void);
igMetaObject *igAnimationHierarchy_GetMetaObject(void);
}
igMetaObject *igAnimationHierarchy_GetMetaObject(void)
{
    igMetaObject *g = g_igAnimationHierarchy_metaObject[0];
    bool t;
    if (!g || !(t = g->_validity & 4))
        FUN_001a71a0();
    return g_igAnimationHierarchy_metaObject[0];
}
