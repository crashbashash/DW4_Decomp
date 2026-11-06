#include "dw4/reflected.h"
extern igMetaObject *g_igIterateGraph_metaObject[4];
extern "C" {
void FUN_00227620(void);
igMetaObject *igIterateGraph_GetMetaObject(void);
}
igMetaObject *igIterateGraph_GetMetaObject(void)
{
    igMetaObject *g = g_igIterateGraph_metaObject[0];
    if (!g || ((g->_validity & 4) != 0) == false)
        FUN_00227620();
    return g_igIterateGraph_metaObject[0];
}
