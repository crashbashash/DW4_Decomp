#include "dw4/reflected.h"
extern igMetaObject *g___internalObjectList_metaObject[4];
extern "C" {
void __internalObjectList_EnsureRegistered(void);
igMetaObject *__internalObjectList_GetMetaObject(void);
}
igMetaObject *__internalObjectList_GetMetaObject(void)
{
    igMetaObject *g = g___internalObjectList_metaObject[0];
    if (!g || ((g->_validity & 4) != 0) == false)
        __internalObjectList_EnsureRegistered();
    return g___internalObjectList_metaObject[0];
}
