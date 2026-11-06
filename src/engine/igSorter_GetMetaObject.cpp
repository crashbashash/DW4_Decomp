#include "dw4/reflected.h"
extern igMetaObject *g_igSorter_metaObject[4];
extern "C" {
void FUN_00197360(void);
igMetaObject *igSorter_GetMetaObject(void);
}
igMetaObject *igSorter_GetMetaObject(void)
{
    igMetaObject *g = g_igSorter_metaObject[0];
    bool t;
    if (!g || !(t = g->_validity & 4))
        FUN_00197360();
    return g_igSorter_metaObject[0];
}
