#include "dw4/reflected.h"
extern igMetaObject *g_igProbe_metaObject[4];
extern "C" {
void FUN_0019e890(void);
igMetaObject *igProbe_GetMetaObject(void);
}
igMetaObject *igProbe_GetMetaObject(void)
{
    igMetaObject *g = g_igProbe_metaObject[0];
    bool t;
    if (!g || !(t = g->_validity & 4))
        FUN_0019e890();
    return g_igProbe_metaObject[0];
}
