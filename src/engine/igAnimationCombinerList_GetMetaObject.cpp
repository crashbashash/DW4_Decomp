#include "dw4/reflected.h"
extern igMetaObject *g_igAnimationCombinerList_metaObject[4];
extern "C" {
void FUN_001a8490(void);
igMetaObject *igAnimationCombinerList_GetMetaObject(void);
}
igMetaObject *igAnimationCombinerList_GetMetaObject(void)
{
    igMetaObject *g = g_igAnimationCombinerList_metaObject[0];
    if (!g || ((g->_validity & 4) != 0) == false)
        FUN_001a8490();
    return g_igAnimationCombinerList_metaObject[0];
}
