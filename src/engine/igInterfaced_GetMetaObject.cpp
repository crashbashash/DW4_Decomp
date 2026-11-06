#include "dw4/reflected.h"
extern igMetaObject *g_igInterfaced_metaObject[4];
extern "C" {
void FUN_00228a20(void);
igMetaObject *igInterfaced_GetMetaObject(void);
}
igMetaObject *igInterfaced_GetMetaObject(void)
{
    igMetaObject *g = g_igInterfaced_metaObject[0];
    bool t;
    if (!g || !(t = g->_validity & 4))
        FUN_00228a20();
    return g_igInterfaced_metaObject[0];
}
