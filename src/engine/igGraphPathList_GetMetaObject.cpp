#include "dw4/reflected.h"
extern igMetaObject *g_igGraphPathList_metaObject[4];
extern "C" {
void FUN_0019f5a0(void);
igMetaObject *igGraphPathList_GetMetaObject(void);
}
igMetaObject *igGraphPathList_GetMetaObject(void)
{
    igMetaObject *g = g_igGraphPathList_metaObject[0];
    if (!g || ((g->_validity & 4) != 0) == false)
        FUN_0019f5a0();
    return g_igGraphPathList_metaObject[0];
}
