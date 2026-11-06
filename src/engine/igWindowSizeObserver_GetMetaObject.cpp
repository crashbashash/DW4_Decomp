#include "dw4/reflected.h"
extern igMetaObject *g_igWindowSizeObserver_metaObject[4];
extern "C" {
void igWindowSizeObserver_RunStaticInit(void);
igMetaObject *igWindowSizeObserver_GetMetaObject(void);
}
igMetaObject *igWindowSizeObserver_GetMetaObject(void)
{
    igMetaObject *g = g_igWindowSizeObserver_metaObject[0];
    bool t;
    if (!g || !(t = g->_validity & 4))
        igWindowSizeObserver_RunStaticInit();
    return g_igWindowSizeObserver_metaObject[0];
}
