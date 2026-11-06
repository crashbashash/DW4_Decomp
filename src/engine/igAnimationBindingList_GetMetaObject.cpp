#include "dw4/reflected.h"
extern igMetaObject *g_igAnimationBindingList_metaObject[4];
extern "C" {
void FUN_001a8ba0(void);
igMetaObject *igAnimationBindingList_GetMetaObject(void);
}
igMetaObject *igAnimationBindingList_GetMetaObject(void)
{
    igMetaObject *g = g_igAnimationBindingList_metaObject[0];
    bool t;
    if (!g || !(t = g->_validity & 4))
        FUN_001a8ba0();
    return g_igAnimationBindingList_metaObject[0];
}
