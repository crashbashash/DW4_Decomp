#include "dw4/reflected.h"
extern igMetaObject *g_igCustomState_metaObject[4];
extern "C" {
void FUN_0014f240(void);
igMetaObject *igCustomState_GetMetaObject(void);
}
igMetaObject *igCustomState_GetMetaObject(void)
{
    igMetaObject *g = g_igCustomState_metaObject[0];
    if (!g || ((g->_validity & 4) != 0) == false)
        FUN_0014f240();
    return g_igCustomState_metaObject[0];
}
