#include "dw4/reflected.h"
extern igMetaObject *g_igHotKeyBindingList_metaObject[4];
extern "C" {
void igHotKeyBindingList_RunStaticInit(void);
igMetaObject *igHotKeyBindingList_GetMetaObject(void);
}
igMetaObject *igHotKeyBindingList_GetMetaObject(void)
{
    igMetaObject *g = g_igHotKeyBindingList_metaObject[0];
    if (!g || ((g->_validity & 4) != 0) == false)
        igHotKeyBindingList_RunStaticInit();
    return g_igHotKeyBindingList_metaObject[0];
}
