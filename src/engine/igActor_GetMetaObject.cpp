#include "dw4/reflected.h"
extern igMetaObject *g_igActor_metaObject[4];
extern "C" {
void FUN_001aaa50(void);
igMetaObject *igActor_GetMetaObject(void);
}
igMetaObject *igActor_GetMetaObject(void)
{
    igMetaObject *g = g_igActor_metaObject[0];
    bool t;
    if (!g || !(t = g->_validity & 4))
        FUN_001aaa50();
    return g_igActor_metaObject[0];
}
