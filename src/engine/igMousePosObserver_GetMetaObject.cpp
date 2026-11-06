#include "dw4/reflected.h"
extern igMetaObject *g_igMousePosObserver_metaObject[4];
extern "C" {
void igMousePosObserver_RunStaticInit(void);
igMetaObject *igMousePosObserver_GetMetaObject(void);
}
igMetaObject *igMousePosObserver_GetMetaObject(void)
{
    igMetaObject *g = g_igMousePosObserver_metaObject[0];
    if (!g || ((g->_validity & 4) != 0) == false)
        igMousePosObserver_RunStaticInit();
    return g_igMousePosObserver_metaObject[0];
}
