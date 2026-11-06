#include "dw4/reflected.h"
extern igMetaObject *g_igContext_metaObject[4];
extern "C" {
void FUN_002cbbb0(void);
igMetaObject *igContext_GetMetaObject(void);
}
igMetaObject *igContext_GetMetaObject(void)
{
    igMetaObject *g = g_igContext_metaObject[0];
    bool t;
    if (!g || !(t = g->_validity & 4))
        FUN_002cbbb0();
    return g_igContext_metaObject[0];
}
