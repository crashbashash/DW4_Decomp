#include "dw4/reflected.h"
extern igMetaObject *g_igEventReceiverOrderedList_metaObject[4];
extern "C" {
void igEventReceiverOrderedList_EnsureRegistered(void);
igMetaObject *igEventReceiverOrderedList_GetMetaObject(void);
}
igMetaObject *igEventReceiverOrderedList_GetMetaObject(void)
{
    igMetaObject *g = g_igEventReceiverOrderedList_metaObject[0];
    bool t;
    if (!g || !(t = g->_validity & 4))
        igEventReceiverOrderedList_EnsureRegistered();
    return g_igEventReceiverOrderedList_metaObject[0];
}
