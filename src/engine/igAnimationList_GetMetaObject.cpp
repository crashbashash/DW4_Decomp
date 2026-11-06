#include "dw4/reflected.h"
extern igMetaObject *g_igAnimationList_metaObject[4];
extern "C" {
void FUN_001a9060(void);
igMetaObject *igAnimationList_GetMetaObject(void);
}
igMetaObject *igAnimationList_GetMetaObject(void)
{
    igMetaObject *g = g_igAnimationList_metaObject[0];
    if (!g || ((g->_validity & 4) != 0) == false)
        FUN_001a9060();
    return g_igAnimationList_metaObject[0];
}
