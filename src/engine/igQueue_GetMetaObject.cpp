#include "dw4/reflected.h"
extern igMetaObject *g_igQueue_metaObject[4];
extern "C" {
void FUN_002bc1b0(void);
igMetaObject *igQueue_GetMetaObject(void);
}
igMetaObject *igQueue_GetMetaObject(void)
{
    igMetaObject *g = g_igQueue_metaObject[0];
    if (!g || ((g->_validity & 4) != 0) == false)
        FUN_002bc1b0();
    return g_igQueue_metaObject[0];
}
