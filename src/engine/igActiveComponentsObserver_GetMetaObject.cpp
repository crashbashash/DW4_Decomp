#include "dw4/reflected.h"
extern igMetaObject *g_igActiveComponentsObserver_metaObject[4];
extern "C" {
void igActiveComponentsObserver_RunStaticInit(void);
igMetaObject *igActiveComponentsObserver_GetMetaObject(void);
}
igMetaObject *igActiveComponentsObserver_GetMetaObject(void)
{
    igMetaObject *g = g_igActiveComponentsObserver_metaObject[0];
    bool t;
    if (!g || !(t = g->_validity & 4))
        igActiveComponentsObserver_RunStaticInit();
    return g_igActiveComponentsObserver_metaObject[0];
}
