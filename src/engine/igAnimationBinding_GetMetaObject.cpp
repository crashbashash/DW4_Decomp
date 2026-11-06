#include "dw4/reflected.h"
extern igMetaObject *g_igAnimationBinding_metaObject[4];
extern "C" {
void FUN_001a8df0(void);
igMetaObject *igAnimationBinding_GetMetaObject(void);
}
igMetaObject *igAnimationBinding_GetMetaObject(void)
{
    igMetaObject *g = g_igAnimationBinding_metaObject[0];
    if (!g || ((g->_validity & 4) != 0) == false)
        FUN_001a8df0();
    return g_igAnimationBinding_metaObject[0];
}
