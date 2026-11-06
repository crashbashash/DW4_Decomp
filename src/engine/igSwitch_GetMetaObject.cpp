#include "dw4/reflected.h"
extern igMetaObject *g_igSwitch_metaObject[4];
extern "C" {
void FUN_00196ad0(void);
igMetaObject *igSwitch_GetMetaObject(void);
}
igMetaObject *igSwitch_GetMetaObject(void)
{
    igMetaObject *g = g_igSwitch_metaObject[0];
    if (!g || ((g->_validity & 4) != 0) == false)
        FUN_00196ad0();
    return g_igSwitch_metaObject[0];
}
