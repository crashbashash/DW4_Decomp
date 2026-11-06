#include "dw4/reflected.h"
extern igMetaObject *g_igContextExtInfoList_metaObject[4];
extern "C" {
void FUN_002cb5d0(void);
igMetaObject *igContextExtInfoList_GetMetaObject(void);
}
igMetaObject *igContextExtInfoList_GetMetaObject(void)
{
    igMetaObject *g = g_igContextExtInfoList_metaObject[0];
    if (!g || ((g->_validity & 4) != 0) == false)
        FUN_002cb5d0();
    return g_igContextExtInfoList_metaObject[0];
}
