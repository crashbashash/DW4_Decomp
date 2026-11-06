#include "dw4/reflected.h"
extern igMetaObject *g_igDirectoryList_metaObject[4];
extern "C" {
void FUN_002c7230(void);
igMetaObject *igDirectoryList_GetMetaObject(void);
}
igMetaObject *igDirectoryList_GetMetaObject(void)
{
    igMetaObject *g = g_igDirectoryList_metaObject[0];
    bool t;
    if (!g || !(t = g->_validity & 4))
        FUN_002c7230();
    return g_igDirectoryList_metaObject[0];
}
