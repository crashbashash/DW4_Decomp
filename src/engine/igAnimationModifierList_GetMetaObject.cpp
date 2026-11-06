#include "dw4/reflected.h"
extern igMetaObject *g_igAnimationModifierList_metaObject[4];
extern "C" {
void FUN_001a73b0(void);
igMetaObject *igAnimationModifierList_GetMetaObject(void);
}
igMetaObject *igAnimationModifierList_GetMetaObject(void)
{
    igMetaObject *g = g_igAnimationModifierList_metaObject[0];
    if (!g || ((g->_validity & 4) != 0) == false)
        FUN_001a73b0();
    return g_igAnimationModifierList_metaObject[0];
}
