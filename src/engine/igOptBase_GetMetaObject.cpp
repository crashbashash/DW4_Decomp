#include "dw4/reflected.h"
extern igMetaObject *g_igOptBase_metaObject[4];
extern "C" {
void FUN_00225f80(void);
igMetaObject *igOptBase_GetMetaObject(void);
}
igMetaObject *igOptBase_GetMetaObject(void)
{
    igMetaObject *g = g_igOptBase_metaObject[0];
    bool t;
    if (!g || !(t = g->_validity & 4))
        FUN_00225f80();
    return g_igOptBase_metaObject[0];
}
