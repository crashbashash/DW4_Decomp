#include "dw4/reflected.h"
extern igMetaObject *g_igInfoList_metaObject[4];
extern "C" {
void FUN_002c3520(void);
igMetaObject *igInfoList_GetMetaObject(void);
}
igMetaObject *igInfoList_GetMetaObject(void)
{
    igMetaObject *g = g_igInfoList_metaObject[0];
    bool t;
    if (!g || !(t = g->_validity & 4))
        FUN_002c3520();
    return g_igInfoList_metaObject[0];
}
