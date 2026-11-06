#include "dw4/reflected.h"
extern igMetaObject *g_igAnimationStatePool_metaObject[4];
extern "C" {
void igAnimationStatePool_RunStaticInit(void);
igMetaObject *igAnimationStatePool_GetMetaObject(void);
}
igMetaObject *igAnimationStatePool_GetMetaObject(void)
{
    igMetaObject *g = g_igAnimationStatePool_metaObject[0];
    bool t;
    if (!g || !(t = g->_validity & 4))
        igAnimationStatePool_RunStaticInit();
    return g_igAnimationStatePool_metaObject[0];
}
