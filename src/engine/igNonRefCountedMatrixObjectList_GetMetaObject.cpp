#include "dw4/reflected.h"
extern igMetaObject *g_igNonRefCountedMatrixObjectList_metaObject[4];
extern "C" {
void FUN_001e4a50(void);
igMetaObject *igNonRefCountedMatrixObjectList_GetMetaObject(void);
}
igMetaObject *igNonRefCountedMatrixObjectList_GetMetaObject(void)
{
    igMetaObject *g = g_igNonRefCountedMatrixObjectList_metaObject[0];
    if (!g || ((g->_validity & 4) != 0) == false)
        FUN_001e4a50();
    return g_igNonRefCountedMatrixObjectList_metaObject[0];
}
