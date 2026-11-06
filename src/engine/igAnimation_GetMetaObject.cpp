#include "dw4/reflected.h"
extern igMetaObject *g_igAnimation_metaObject[4];
extern "C" {
void FUN_001a9290(void);
igMetaObject *igAnimation_GetMetaObject(void);
}
igMetaObject *igAnimation_GetMetaObject(void)
{
    igMetaObject *g = g_igAnimation_metaObject[0];
    bool t;
    if (!g || !(t = g->_validity & 4))
        FUN_001a9290();
    return g_igAnimation_metaObject[0];
}
