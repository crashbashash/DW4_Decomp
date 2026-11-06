#include "dw4/reflected.h"
extern igMetaObject *g_igIterateDerived_metaObject[4];
extern "C" {
void FUN_00227af0(void);
igMetaObject *igIterateDerived_GetMetaObject(void);
}
igMetaObject *igIterateDerived_GetMetaObject(void)
{
    igMetaObject *g = g_igIterateDerived_metaObject[0];
    if (!g || ((g->_validity & 4) != 0) == false)
        FUN_00227af0();
    return g_igIterateDerived_metaObject[0];
}
