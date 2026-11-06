#include "dw4/reflected.h"
extern igMetaObject *g_igEnbayaContextPool_metaObject[4];
extern "C" {
void igEnbayaContextPool_RunStaticInit(void);
igMetaObject *igEnbayaContextPool_GetMetaObject(void);
}
igMetaObject *igEnbayaContextPool_GetMetaObject(void)
{
    igMetaObject *g = g_igEnbayaContextPool_metaObject[0];
    bool t;
    if (!g || !(t = g->_validity & 4))
        igEnbayaContextPool_RunStaticInit();
    return g_igEnbayaContextPool_metaObject[0];
}
