#include "dw4/reflected.h"
extern igMetaObject *g_igOptInterface_metaObject[4];
extern "C" {
void FUN_00225c10(void);
igMetaObject *igOptInterface_GetMetaObject(void);
}
igMetaObject *igOptInterface_GetMetaObject(void)
{
    igMetaObject *g = g_igOptInterface_metaObject[0];
    if (!g || ((g->_validity & 4) != 0) == false)
        FUN_00225c10();
    return g_igOptInterface_metaObject[0];
}
