#include "dw4/reflected.h"
extern igMetaObject *g_igStringTable_metaObject[4];
extern "C" {
void FUN_002b8f90(void);
igMetaObject *igStringTable_GetMetaObject(void);
}
igMetaObject *igStringTable_GetMetaObject(void)
{
    igMetaObject *g = g_igStringTable_metaObject[0];
    if (!g || ((g->_validity & 4) != 0) == false)
        FUN_002b8f90();
    return g_igStringTable_metaObject[0];
}
