#include "dw4/reflected.h"
extern igMetaObject *g_igNonRefCountedTransformList_metaObject[4];
extern "C" {
void FUN_00195de0(void);
igMetaObject *igNonRefCountedTransformList_GetMetaObject(void);
}
igMetaObject *igNonRefCountedTransformList_GetMetaObject(void)
{
    igMetaObject *g = g_igNonRefCountedTransformList_metaObject[0];
    if (!g || ((g->_validity & 4) != 0) == false)
        FUN_00195de0();
    return g_igNonRefCountedTransformList_metaObject[0];
}
