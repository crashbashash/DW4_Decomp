#include "dw4/reflected.h"
extern igMetaObject *g_igContextList_metaObject[4];
extern "C" {
void FUN_002cbad0(void);
igMetaObject *igContextList_GetMetaObject(void);
}
igMetaObject *igContextList_GetMetaObject(void)
{
    igMetaObject *g = g_igContextList_metaObject[0];
    if (!g || ((g->_validity & 4) != 0) == false)
        FUN_002cbad0();
    return g_igContextList_metaObject[0];
}
