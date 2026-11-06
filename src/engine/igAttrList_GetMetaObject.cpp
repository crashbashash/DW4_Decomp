#include "dw4/reflected.h"
extern igMetaObject *g_igAttrList_metaObject[4];
extern "C" {
void FUN_0013afe0(void);
igMetaObject *igAttrList_GetMetaObject(void);
}
igMetaObject *igAttrList_GetMetaObject(void)
{
    igMetaObject *g = g_igAttrList_metaObject[0];
    bool t;
    if (!g || !(t = g->_validity & 4))
        FUN_0013afe0();
    return g_igAttrList_metaObject[0];
}
