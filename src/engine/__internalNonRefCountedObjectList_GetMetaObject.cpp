#include "dw4/reflected.h"
extern igMetaObject *g___internalNonRefCountedObjectList_metaObject[4];
extern "C" {
void FUN_002c2bb0(void);
igMetaObject *__internalNonRefCountedObjectList_GetMetaObject(void);
}
igMetaObject *__internalNonRefCountedObjectList_GetMetaObject(void)
{
    igMetaObject *g = g___internalNonRefCountedObjectList_metaObject[0];
    bool t;
    if (!g || !(t = g->_validity & 4))
        FUN_002c2bb0();
    return g___internalNonRefCountedObjectList_metaObject[0];
}
