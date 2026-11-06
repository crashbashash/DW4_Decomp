#include "dw4/reflected.h"
extern igMetaObject *g_igBase_metaObject[4];
extern "C" {
void FUN_002292d0(void);
igMetaObject *igBase_GetMetaObject(void);
}
igMetaObject *igBase_GetMetaObject(void)
{
    igMetaObject *g = g_igBase_metaObject[0];
    bool t;
    if (!g || !(t = g->_validity & 4))
        FUN_002292d0();
    return g_igBase_metaObject[0];
}
