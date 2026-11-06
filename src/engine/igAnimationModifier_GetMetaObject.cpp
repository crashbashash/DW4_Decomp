#include "dw4/reflected.h"
extern igMetaObject *g_igAnimationModifier_metaObject[4];
extern "C" {
void FUN_001a7600(void);
igMetaObject *igAnimationModifier_GetMetaObject(void);
}
igMetaObject *igAnimationModifier_GetMetaObject(void)
{
    igMetaObject *g = g_igAnimationModifier_metaObject[0];
    if (!g || ((g->_validity & 4) != 0) == false)
        FUN_001a7600();
    return g_igAnimationModifier_metaObject[0];
}
