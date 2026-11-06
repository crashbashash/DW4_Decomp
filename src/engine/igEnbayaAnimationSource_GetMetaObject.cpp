#include "dw4/reflected.h"
extern igMetaObject *g_igEnbayaAnimationSource_metaObject[4];
extern "C" {
void FUN_001a22f0(void);
igMetaObject *igEnbayaAnimationSource_GetMetaObject(void);
}
igMetaObject *igEnbayaAnimationSource_GetMetaObject(void)
{
    igMetaObject *g = g_igEnbayaAnimationSource_metaObject[0];
    if (!g || ((g->_validity & 4) != 0) == false)
        FUN_001a22f0();
    return g_igEnbayaAnimationSource_metaObject[0];
}
