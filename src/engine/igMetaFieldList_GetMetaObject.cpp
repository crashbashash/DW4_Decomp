#include "dw4/reflected.h"
extern igMetaObject *g_igMetaFieldList_metaObject[4];
extern "C" {
void FUN_002c8c10(void);
igMetaObject *igMetaFieldList_GetMetaObject(void);
}
igMetaObject *igMetaFieldList_GetMetaObject(void)
{
    igMetaObject *g = g_igMetaFieldList_metaObject[0];
    if (!g || ((g->_validity & 4) != 0) == false)
        FUN_002c8c10();
    return g_igMetaFieldList_metaObject[0];
}
