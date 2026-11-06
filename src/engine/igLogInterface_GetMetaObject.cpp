#include "dw4/reflected.h"
extern igMetaObject *g_igLogInterface_metaObject[4];
extern "C" {
void FUN_002266c0(void);
igMetaObject *igLogInterface_GetMetaObject(void);
}
igMetaObject *igLogInterface_GetMetaObject(void)
{
    igMetaObject *g = g_igLogInterface_metaObject[0];
    if (!g || ((g->_validity & 4) != 0) == false)
        FUN_002266c0();
    return g_igLogInterface_metaObject[0];
}
