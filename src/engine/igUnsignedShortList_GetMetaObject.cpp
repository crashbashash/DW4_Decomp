#include "dw4/reflected.h"
extern igMetaObject *g_igUnsignedShortList_metaObject[4];
extern "C" {
void FUN_002ca110(void);
igMetaObject *igUnsignedShortList_GetMetaObject(void);
}
igMetaObject *igUnsignedShortList_GetMetaObject(void)
{
    igMetaObject *g = g_igUnsignedShortList_metaObject[0];
    if (!g || ((g->_validity & 4) != 0) == false)
        FUN_002ca110();
    return g_igUnsignedShortList_metaObject[0];
}
