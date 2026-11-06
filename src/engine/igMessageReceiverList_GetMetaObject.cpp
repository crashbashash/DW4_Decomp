#include "dw4/reflected.h"
extern igMetaObject *g_igMessageReceiverList_metaObject[4];
extern "C" {
void FUN_00231870(void);
igMetaObject *igMessageReceiverList_GetMetaObject(void);
}
igMetaObject *igMessageReceiverList_GetMetaObject(void)
{
    igMetaObject *g = g_igMessageReceiverList_metaObject[0];
    if (!g || ((g->_validity & 4) != 0) == false)
        FUN_00231870();
    return g_igMessageReceiverList_metaObject[0];
}
