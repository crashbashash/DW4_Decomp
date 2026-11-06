#include "dw4/reflected.h"
extern igMetaObject *g_igLocationTable_metaObject[4];
extern "C" {
void FUN_002c20f0(void);
igMetaObject *igLocationTable_GetMetaObject(void);
}
igMetaObject *igLocationTable_GetMetaObject(void)
{
    igMetaObject *g = g_igLocationTable_metaObject[0];
    bool t;
    if (!g || !(t = g->_validity & 4))
        FUN_002c20f0();
    return g_igLocationTable_metaObject[0];
}
