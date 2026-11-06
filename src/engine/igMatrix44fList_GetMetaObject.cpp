#include "dw4/reflected.h"
extern igMetaObject *g_igMatrix44fList_metaObject[4];
extern "C" {
void FUN_00189a80(void);
igMetaObject *igMatrix44fList_GetMetaObject(void);
}
igMetaObject *igMatrix44fList_GetMetaObject(void)
{
    igMetaObject *g = g_igMatrix44fList_metaObject[0];
    bool t;
    if (!g || !(t = g->_validity & 4))
        FUN_00189a80();
    return g_igMatrix44fList_metaObject[0];
}
