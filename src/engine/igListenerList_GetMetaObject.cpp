#include "dw4/reflected.h"
extern igMetaObject *g_igListenerList_metaObject[4];
extern "C" {
void FUN_002271d0(void);
igMetaObject *igListenerList_GetMetaObject(void);
}
igMetaObject *igListenerList_GetMetaObject(void)
{
    igMetaObject *g = g_igListenerList_metaObject[0];
    if (!g || ((g->_validity & 4) != 0) == false)
        FUN_002271d0();
    return g_igListenerList_metaObject[0];
}
