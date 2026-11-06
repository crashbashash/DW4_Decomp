#include "dw4/reflected.h"
extern igMetaObject *g_igThread_metaObject[4];
extern "C" {
void FUN_002b8020(void);
igMetaObject *igThread_GetMetaObject(void);
}
igMetaObject *igThread_GetMetaObject(void)
{
    igMetaObject *g = g_igThread_metaObject[0];
    if (!g || ((g->_validity & 4) != 0) == false)
        FUN_002b8020();
    return g_igThread_metaObject[0];
}
