#include "dw4/reflected.h"
extern igMetaObject *g_igNonRefCountedObjectStack_metaObject[4];
extern "C" {
void FUN_001e4430(void);
igMetaObject *igNonRefCountedObjectStack_GetMetaObject(void);
}
igMetaObject *igNonRefCountedObjectStack_GetMetaObject(void)
{
    igMetaObject *g = g_igNonRefCountedObjectStack_metaObject[0];
    if (!g || ((g->_validity & 4) != 0) == false)
        FUN_001e4430();
    return g_igNonRefCountedObjectStack_metaObject[0];
}
