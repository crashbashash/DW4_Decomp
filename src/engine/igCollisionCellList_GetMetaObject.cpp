#include "dw4/reflected.h"
extern igMetaObject *g_igCollisionCellList_metaObject[4];
extern "C" {
void FUN_0023a650(void);
igMetaObject *igCollisionCellList_GetMetaObject(void);
}
igMetaObject *igCollisionCellList_GetMetaObject(void)
{
    igMetaObject *g = g_igCollisionCellList_metaObject[0];
    bool t;
    if (!g || !(t = g->_validity & 4))
        FUN_0023a650();
    return g_igCollisionCellList_metaObject[0];
}
