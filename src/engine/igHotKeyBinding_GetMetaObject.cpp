#include "dw4/reflected.h"
extern igMetaObject *g_igHotKeyBinding_metaObject[4];
extern "C" {
void igHotKeyBinding_RunStaticInit(void);
igMetaObject *igHotKeyBinding_GetMetaObject(void);
}
igMetaObject *igHotKeyBinding_GetMetaObject(void)
{
    igMetaObject *g = g_igHotKeyBinding_metaObject[0];
    if (!g || ((g->_validity & 4) != 0) == false)
        igHotKeyBinding_RunStaticInit();
    return g_igHotKeyBinding_metaObject[0];
}
