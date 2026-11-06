#include "dw4/reflected.h"
extern igMetaObject *g_igNonRefCountedObjectList_metaObject[4];
extern "C" {
void FUN_002bdd30(void);
igMetaObject *igNonRefCountedObjectList_GetMetaObject(void);
}
igMetaObject *igNonRefCountedObjectList_GetMetaObject(void)
{
    igMetaObject *g = g_igNonRefCountedObjectList_metaObject[0];
    bool t;
    if (!g || !(t = g->_validity & 4))
        FUN_002bdd30();
    return g_igNonRefCountedObjectList_metaObject[0];
}
