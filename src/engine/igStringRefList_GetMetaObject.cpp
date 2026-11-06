#include "dw4/reflected.h"
extern igMetaObject *g_igStringRefList_metaObject[4];
extern "C" {
void FUN_002b9200(void);
igMetaObject *igStringRefList_GetMetaObject(void);
}
igMetaObject *igStringRefList_GetMetaObject(void)
{
    igMetaObject *g = g_igStringRefList_metaObject[0];
    if (!g || ((g->_validity & 4) != 0) == false)
        FUN_002b9200();
    return g_igStringRefList_metaObject[0];
}
