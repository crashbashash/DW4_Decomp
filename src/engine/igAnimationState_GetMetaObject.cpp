#include "dw4/reflected.h"
extern igMetaObject *g_igAnimationState_metaObject[4];
extern "C" {
void FUN_001a6dc0(void);
igMetaObject *igAnimationState_GetMetaObject(void);
}
igMetaObject *igAnimationState_GetMetaObject(void)
{
    igMetaObject *g = g_igAnimationState_metaObject[0];
    bool t;
    if (!g || !(t = g->_validity & 4))
        FUN_001a6dc0();
    return g_igAnimationState_metaObject[0];
}
