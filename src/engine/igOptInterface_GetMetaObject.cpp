#include "dw4/reflected.h"
extern igMetaObject *g_igOptInterface_metaObject[4];
extern "C" {
void FUN_00225c10(void);
igMetaObject *igOptInterface_GetMetaObject(void);
}
igMetaObject *igOptInterface_GetMetaObject(void)
{
    igMetaObject *g = g_igOptInterface_metaObject[0];
    bool t;
    if (!g || !(t = g->_validity & 4))
        FUN_00225c10();
    return g_igOptInterface_metaObject[0];
}
