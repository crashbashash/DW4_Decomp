#include "dw4/reflected.h"
extern igMetaObject *g_igTrackedElementMetaField_metaObject[4];
extern "C" {
void FUN_0014e4a0(void);
igMetaObject *igTrackedElementMetaField_GetMetaObject(void);
}
igMetaObject *igTrackedElementMetaField_GetMetaObject(void)
{
    igMetaObject *g = g_igTrackedElementMetaField_metaObject[0];
    if (!g || ((g->_validity & 4) != 0) == false)
        FUN_0014e4a0();
    return g_igTrackedElementMetaField_metaObject[0];
}
