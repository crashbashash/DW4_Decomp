#include "dw4/reflected.h"
extern igMetaObject *g_igAttrList_metaObject[4];
extern "C" {
void FUN_0013afe0(void);
igMetaObject *igAttrList_GetMetaObject(void);
}
igMetaObject *igAttrList_GetMetaObject(void)
{
    igMetaObject *g = g_igAttrList_metaObject[0];
    if (!g || ((g->_validity & 4) != 0) == false)
        FUN_0013afe0();
    return g_igAttrList_metaObject[0];
}
