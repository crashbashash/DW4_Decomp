#include "dw4/reflected.h"
extern igMetaObject *g_igNodeList_metaObject[4];
extern "C" {
void FUN_0019ccc0(void);
igMetaObject *igNodeList_GetMetaObject(void);
}
igMetaObject *igNodeList_GetMetaObject(void)
{
    igMetaObject *g = g_igNodeList_metaObject[0];
    bool t;
    if (!g || !(t = g->_validity & 4))
        FUN_0019ccc0();
    return g_igNodeList_metaObject[0];
}
