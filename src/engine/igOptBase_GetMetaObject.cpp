#include "dw4/reflected.h"
extern igMetaObject *g_igOptBase_metaObject[4];
extern "C" {
void FUN_00225f80(void);
igMetaObject *igOptBase_GetMetaObject(void);
}
igMetaObject *igOptBase_GetMetaObject(void)
{
    igMetaObject *g = g_igOptBase_metaObject[0];
    if (!g || ((g->_validity & 4) != 0) == false)
        FUN_00225f80();
    return g_igOptBase_metaObject[0];
}
