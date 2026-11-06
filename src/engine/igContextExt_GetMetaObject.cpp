#include "dw4/reflected.h"
extern igMetaObject *g_igContextExt_metaObject[4];
extern "C" {
void FUN_002cb980(void);
igMetaObject *igContextExt_GetMetaObject(void);
}
igMetaObject *igContextExt_GetMetaObject(void)
{
    igMetaObject *g = g_igContextExt_metaObject[0];
    bool t;
    if (!g || !(t = g->_validity & 4))
        FUN_002cb980();
    return g_igContextExt_metaObject[0];
}
