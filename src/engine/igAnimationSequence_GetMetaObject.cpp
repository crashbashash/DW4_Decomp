#include "dw4/reflected.h"
extern igMetaObject *g_igAnimationSequence_metaObject[4];
extern "C" {
void FUN_001a7080(void);
igMetaObject *igAnimationSequence_GetMetaObject(void);
}
igMetaObject *igAnimationSequence_GetMetaObject(void)
{
    igMetaObject *g = g_igAnimationSequence_metaObject[0];
    if (!g || ((g->_validity & 4) != 0) == false)
        FUN_001a7080();
    return g_igAnimationSequence_metaObject[0];
}
