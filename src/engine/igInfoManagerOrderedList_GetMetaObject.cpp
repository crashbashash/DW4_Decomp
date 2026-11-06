#include "dw4/reflected.h"
extern igMetaObject *g_igInfoManagerOrderedList_metaObject[4];
extern "C" {
void FUN_002336b0(void);
igMetaObject *igInfoManagerOrderedList_GetMetaObject(void);
}
igMetaObject *igInfoManagerOrderedList_GetMetaObject(void)
{
    igMetaObject *g = g_igInfoManagerOrderedList_metaObject[0];
    if (!g || ((g->_validity & 4) != 0) == false)
        FUN_002336b0();
    return g_igInfoManagerOrderedList_metaObject[0];
}
