#include "dw4/reflected.h"
extern igMetaObject *g_igEnbayaContextPool_metaObject[4];
extern "C" {
void igEnbayaContextPool_RunStaticInit(void);
igMetaObject *igEnbayaContextPool_GetMetaObject(void);
}
igMetaObject *igEnbayaContextPool_GetMetaObject(void)
{
    igMetaObject *g = g_igEnbayaContextPool_metaObject[0];
    if (!g || ((g->_validity & 4) != 0) == false)
        igEnbayaContextPool_RunStaticInit();
    return g_igEnbayaContextPool_metaObject[0];
}
