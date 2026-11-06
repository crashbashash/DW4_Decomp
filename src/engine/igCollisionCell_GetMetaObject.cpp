#include "dw4/reflected.h"
extern igMetaObject *g_igCollisionCell_metaObject[4];
extern "C" {
void FUN_0023a850(void);
igMetaObject *igCollisionCell_GetMetaObject(void);
}
igMetaObject *igCollisionCell_GetMetaObject(void)
{
    igMetaObject *g = g_igCollisionCell_metaObject[0];
    if (!g || ((g->_validity & 4) != 0) == false)
        FUN_0023a850();
    return g_igCollisionCell_metaObject[0];
}
