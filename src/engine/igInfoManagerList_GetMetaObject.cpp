#include "dw4/reflected.h"
extern igMetaObject *g_igInfoManagerList_metaObject[4];
extern "C" {
void FUN_00233830(void);
igMetaObject *igInfoManagerList_GetMetaObject(void);
}
igMetaObject *igInfoManagerList_GetMetaObject(void)
{
    igMetaObject *g = g_igInfoManagerList_metaObject[0];
    if (!g || ((g->_validity & 4) != 0) == false)
        FUN_00233830();
    return g_igInfoManagerList_metaObject[0];
}
