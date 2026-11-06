#include "dw4/reflected.h"
extern igMetaObject *g_igListenerListList_metaObject[4];
extern "C" {
void FUN_002270b0(void);
igMetaObject *igListenerListList_GetMetaObject(void);
}
igMetaObject *igListenerListList_GetMetaObject(void)
{
    igMetaObject *g = g_igListenerListList_metaObject[0];
    if (!g || ((g->_validity & 4) != 0) == false)
        FUN_002270b0();
    return g_igListenerListList_metaObject[0];
}
