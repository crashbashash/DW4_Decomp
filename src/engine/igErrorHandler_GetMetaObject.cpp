#include "dw4/reflected.h"
extern igMetaObject *g_igErrorHandler_metaObject[4];
extern "C" {
void FUN_002c5ee0(void);
igMetaObject *igErrorHandler_GetMetaObject(void);
}
igMetaObject *igErrorHandler_GetMetaObject(void)
{
    igMetaObject *g = g_igErrorHandler_metaObject[0];
    bool t;
    if (!g || !(t = g->_validity & 4))
        FUN_002c5ee0();
    return g_igErrorHandler_metaObject[0];
}
