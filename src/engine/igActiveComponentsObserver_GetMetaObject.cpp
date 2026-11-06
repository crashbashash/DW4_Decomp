#include "dw4/reflected.h"
extern igMetaObject *g_igActiveComponentsObserver_metaObject[4];
extern "C" {
void igActiveComponentsObserver_RunStaticInit(void);
igMetaObject *igActiveComponentsObserver_GetMetaObject(void);
}
igMetaObject *igActiveComponentsObserver_GetMetaObject(void)
{
    igMetaObject *g = g_igActiveComponentsObserver_metaObject[0];
    if (!g || ((g->_validity & 4) != 0) == false)
        igActiveComponentsObserver_RunStaticInit();
    return g_igActiveComponentsObserver_metaObject[0];
}
