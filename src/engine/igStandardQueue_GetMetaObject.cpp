#include "dw4/reflected.h"
extern igMetaObject *g_igStandardQueue_metaObject[4];
extern "C" {
void FUN_002cf0e0(void);
igMetaObject *igStandardQueue_GetMetaObject(void);
}
igMetaObject *igStandardQueue_GetMetaObject(void)
{
    igMetaObject *g = g_igStandardQueue_metaObject[0];
    if (!g || ((g->_validity & 4) != 0) == false)
        FUN_002cf0e0();
    return g_igStandardQueue_metaObject[0];
}
