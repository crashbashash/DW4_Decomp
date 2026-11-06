#include "dw4/reflected.h"
extern igMetaObject *g_igAnimationStateList_metaObject[4];
extern "C" {
void FUN_001a6a00(void);
igMetaObject *igAnimationStateList_GetMetaObject(void);
}
igMetaObject *igAnimationStateList_GetMetaObject(void)
{
    igMetaObject *g = g_igAnimationStateList_metaObject[0];
    if (!g || ((g->_validity & 4) != 0) == false)
        FUN_001a6a00();
    return g_igAnimationStateList_metaObject[0];
}
