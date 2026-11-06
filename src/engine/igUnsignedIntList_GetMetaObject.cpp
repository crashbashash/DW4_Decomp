#include "dw4/reflected.h"
extern igMetaObject *g_igUnsignedIntList_metaObject[4];
extern "C" {
void FUN_002ca530(void);
igMetaObject *igUnsignedIntList_GetMetaObject(void);
}
igMetaObject *igUnsignedIntList_GetMetaObject(void)
{
    igMetaObject *g = g_igUnsignedIntList_metaObject[0];
    if (!g || ((g->_validity & 4) != 0) == false)
        FUN_002ca530();
    return g_igUnsignedIntList_metaObject[0];
}
