#include "dw4/reflected.h"
extern igMetaObject *g_igAttrListList_metaObject[4];
extern "C" {
void FUN_0013acb0(void);
igMetaObject *igAttrListList_GetMetaObject(void);
}
igMetaObject *igAttrListList_GetMetaObject(void)
{
    igMetaObject *g = g_igAttrListList_metaObject[0];
    if (!g || ((g->_validity & 4) != 0) == false)
        FUN_0013acb0();
    return g_igAttrListList_metaObject[0];
}
