#include "dw4/reflected.h"
extern igMetaObject *g_igBoolObject_metaObject[4];
extern "C" {
void FUN_001e5ce0(void);
igMetaObject *igBoolObject_GetMetaObject(void);
}
igMetaObject *igBoolObject_GetMetaObject(void)
{
    igMetaObject *g = g_igBoolObject_metaObject[0];
    if (!g || ((g->_validity & 4) != 0) == false)
        FUN_001e5ce0();
    return g_igBoolObject_metaObject[0];
}
