#include "dw4/reflected.h"
extern igMetaObject *g_igCollisionCellList_metaObject[4];
extern "C" {
void FUN_0023a650(void);
igMetaObject *igCollisionCellList_GetMetaObject(void);
}
igMetaObject *igCollisionCellList_GetMetaObject(void)
{
    igMetaObject *g = g_igCollisionCellList_metaObject[0];
    if (!g || ((g->_validity & 4) != 0) == false)
        FUN_0023a650();
    return g_igCollisionCellList_metaObject[0];
}
