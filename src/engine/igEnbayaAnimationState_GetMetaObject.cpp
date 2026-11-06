#include "dw4/reflected.h"
extern igMetaObject *g_igEnbayaAnimationState_metaObject[4];
extern "C" {
void FUN_001a2030(void);
igMetaObject *igEnbayaAnimationState_GetMetaObject(void);
}
igMetaObject *igEnbayaAnimationState_GetMetaObject(void)
{
    igMetaObject *g = g_igEnbayaAnimationState_metaObject[0];
    bool t;
    if (!g || !(t = g->_validity & 4))
        FUN_001a2030();
    return g_igEnbayaAnimationState_metaObject[0];
}
