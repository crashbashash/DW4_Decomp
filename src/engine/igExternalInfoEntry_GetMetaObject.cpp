#include "dw4/reflected.h"
extern igMetaObject *g_igExternalInfoEntry_metaObject[4];
extern "C" {
void FUN_002c50a0(void);
igMetaObject *igExternalInfoEntry_GetMetaObject(void);
}
igMetaObject *igExternalInfoEntry_GetMetaObject(void)
{
    igMetaObject *g = g_igExternalInfoEntry_metaObject[0];
    bool t;
    if (!g || !(t = g->_validity & 4))
        FUN_002c50a0();
    return g_igExternalInfoEntry_metaObject[0];
}
