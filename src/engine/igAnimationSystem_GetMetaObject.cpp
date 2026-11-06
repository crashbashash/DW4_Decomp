#include "dw4/reflected.h"
extern igMetaObject *g_igAnimationSystem_metaObject[4];
extern "C" {
void FUN_001a66a0(void);
igMetaObject *igAnimationSystem_GetMetaObject(void);
}
igMetaObject *igAnimationSystem_GetMetaObject(void)
{
    igMetaObject *g = g_igAnimationSystem_metaObject[0];
    if (!g || ((g->_validity & 4) != 0) == false)
        FUN_001a66a0();
    return g_igAnimationSystem_metaObject[0];
}
