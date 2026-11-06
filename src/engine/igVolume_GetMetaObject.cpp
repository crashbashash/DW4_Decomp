#include "dw4/reflected.h"
extern igMetaObject *g_igVolume_metaObject[4];
extern "C" {
void FUN_00186b20(void);
igMetaObject *igVolume_GetMetaObject(void);
}
igMetaObject *igVolume_GetMetaObject(void)
{
    igMetaObject *g = g_igVolume_metaObject[0];
    if (!g || ((g->_validity & 4) != 0) == false)
        FUN_00186b20();
    return g_igVolume_metaObject[0];
}
