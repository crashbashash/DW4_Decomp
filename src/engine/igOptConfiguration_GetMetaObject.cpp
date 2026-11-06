#include "dw4/reflected.h"
extern igMetaObject *g_igOptConfiguration_metaObject[4];
extern "C" {
void FUN_00225ea0(void);
igMetaObject *igOptConfiguration_GetMetaObject(void);
}
igMetaObject *igOptConfiguration_GetMetaObject(void)
{
    igMetaObject *g = g_igOptConfiguration_metaObject[0];
    if (!g || ((g->_validity & 4) != 0) == false)
        FUN_00225ea0();
    return g_igOptConfiguration_metaObject[0];
}
