#include "dw4/reflected.h"
extern igMetaObject *g_igRegistry_metaObject[4];
extern "C" {
void FUN_002bb200(void);
igMetaObject *igRegistry_GetMetaObject(void);
}
igMetaObject *igRegistry_GetMetaObject(void)
{
    igMetaObject *g = g_igRegistry_metaObject[0];
    bool t;
    if (!g || !(t = g->_validity & 4))
        FUN_002bb200();
    return g_igRegistry_metaObject[0];
}
