#include "dw4/reflected.h"
extern igMetaObject *g_igThreadManager_metaObject[4];
extern "C" {
void FUN_002b7c00(void);
igMetaObject *igThreadManager_GetMetaObject(void);
}
igMetaObject *igThreadManager_GetMetaObject(void)
{
    igMetaObject *g = g_igThreadManager_metaObject[0];
    if (!g || ((g->_validity & 4) != 0) == false)
        FUN_002b7c00();
    return g_igThreadManager_metaObject[0];
}
