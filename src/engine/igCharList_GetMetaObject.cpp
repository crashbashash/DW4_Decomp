#include "dw4/reflected.h"
extern igMetaObject *g_igCharList_metaObject[4];
extern "C" {
void FUN_002caf80(void);
igMetaObject *igCharList_GetMetaObject(void);
}
igMetaObject *igCharList_GetMetaObject(void)
{
    igMetaObject *g = g_igCharList_metaObject[0];
    if (!g || ((g->_validity & 4) != 0) == false)
        FUN_002caf80();
    return g_igCharList_metaObject[0];
}
