#include "dw4/reflected.h"
extern igMetaObject *g_igIntObject_metaObject[4];
extern "C" {
void FUN_001e4ec0(void);
igMetaObject *igIntObject_GetMetaObject(void);
}
igMetaObject *igIntObject_GetMetaObject(void)
{
    igMetaObject *g = g_igIntObject_metaObject[0];
    bool t;
    if (!g || !(t = g->_validity & 4))
        FUN_001e4ec0();
    return g_igIntObject_metaObject[0];
}
