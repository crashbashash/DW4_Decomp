#include "dw4/reflected.h"
extern igMetaObject *g_igActor_metaObject[4];
extern "C" {
void FUN_001aaa50(void);
igMetaObject *igActor_GetMetaObject(void);
}
igMetaObject *igActor_GetMetaObject(void)
{
    igMetaObject *g = g_igActor_metaObject[0];
    if (!g || ((g->_validity & 4) != 0) == false)
        FUN_001aaa50();
    return g_igActor_metaObject[0];
}
