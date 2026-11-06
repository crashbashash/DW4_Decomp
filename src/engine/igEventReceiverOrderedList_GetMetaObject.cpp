#include "dw4/reflected.h"
extern igMetaObject *g_igEventReceiverOrderedList_metaObject[4];
extern "C" {
void igEventReceiverOrderedList_EnsureRegistered(void);
igMetaObject *igEventReceiverOrderedList_GetMetaObject(void);
}
igMetaObject *igEventReceiverOrderedList_GetMetaObject(void)
{
    igMetaObject *g = g_igEventReceiverOrderedList_metaObject[0];
    if (!g || ((g->_validity & 4) != 0) == false)
        igEventReceiverOrderedList_EnsureRegistered();
    return g_igEventReceiverOrderedList_metaObject[0];
}
