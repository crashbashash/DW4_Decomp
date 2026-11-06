#include "dw4/reflected.h"
extern igMetaObject *g_igUnsignedCharList_metaObject[4];
extern "C" {
void FUN_002c9a80(void);
igMetaObject *igUnsignedCharList_GetMetaObject(void);
}
igMetaObject *igUnsignedCharList_GetMetaObject(void)
{
    igMetaObject *g = g_igUnsignedCharList_metaObject[0];
    if (!g || ((g->_validity & 4) != 0) == false)
        FUN_002c9a80();
    return g_igUnsignedCharList_metaObject[0];
}
