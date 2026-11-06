#include "dw4/reflected.h"
extern igMetaObject *g_igMetaEnum_metaObject[4];
extern "C" {
void FUN_002bf190(void);
igMetaObject *igMetaEnum_GetMetaObject(void);
}
igMetaObject *igMetaEnum_GetMetaObject(void)
{
    igMetaObject *g = g_igMetaEnum_metaObject[0];
    bool t;
    if (!g || !(t = g->_validity & 4))
        FUN_002bf190();
    return g_igMetaEnum_metaObject[0];
}
