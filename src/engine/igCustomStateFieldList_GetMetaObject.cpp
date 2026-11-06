#include "dw4/reflected.h"
extern igMetaObject *g_igCustomStateFieldList_metaObject[4];
extern "C" {
void FUN_0014ea50(void);
igMetaObject *igCustomStateFieldList_GetMetaObject(void);
}
igMetaObject *igCustomStateFieldList_GetMetaObject(void)
{
    igMetaObject *g = g_igCustomStateFieldList_metaObject[0];
    bool t;
    if (!g || !(t = g->_validity & 4))
        FUN_0014ea50();
    return g_igCustomStateFieldList_metaObject[0];
}
