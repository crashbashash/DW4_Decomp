#include "dw4/reflected.h"
extern igMetaObject *g_igVolumeList_metaObject[4];
extern "C" {
void FUN_00186d20(void);
igMetaObject *igVolumeList_GetMetaObject(void);
}
igMetaObject *igVolumeList_GetMetaObject(void)
{
    igMetaObject *g = g_igVolumeList_metaObject[0];
    if (!g || ((g->_validity & 4) != 0) == false)
        FUN_00186d20();
    return g_igVolumeList_metaObject[0];
}
