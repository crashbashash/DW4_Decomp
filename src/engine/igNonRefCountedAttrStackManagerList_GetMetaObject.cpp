#include "dw4/reflected.h"
extern igMetaObject *g_igNonRefCountedAttrStackManagerList_metaObject[4];
extern "C" {
void FUN_001a52a0(void);
igMetaObject *igNonRefCountedAttrStackManagerList_GetMetaObject(void);
}
igMetaObject *igNonRefCountedAttrStackManagerList_GetMetaObject(void)
{
    igMetaObject *g = g_igNonRefCountedAttrStackManagerList_metaObject[0];
    if (!g || ((g->_validity & 4) != 0) == false)
        FUN_001a52a0();
    return g_igNonRefCountedAttrStackManagerList_metaObject[0];
}
