#include "dw4/reflected.h"
extern igMetaObject *g_igNonRefCountedAttrList_metaObject[4];
extern "C" {
void FUN_0013ae20(void);
igMetaObject *igNonRefCountedAttrList_GetMetaObject(void);
}
igMetaObject *igNonRefCountedAttrList_GetMetaObject(void)
{
    igMetaObject *g = g_igNonRefCountedAttrList_metaObject[0];
    if (!g || ((g->_validity & 4) != 0) == false)
        FUN_0013ae20();
    return g_igNonRefCountedAttrList_metaObject[0];
}
