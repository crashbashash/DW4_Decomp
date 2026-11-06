#include "dw4/reflected.h"
extern igMetaObject *g_igMemoryPoolContextInfo_metaObject_00585e88[4];
extern "C" {
void FUN_002c0360(void);
igMetaObject *igMemoryPoolContextInfo_GetMetaObject(void);
}
igMetaObject *igMemoryPoolContextInfo_GetMetaObject(void)
{
    igMetaObject *g = g_igMemoryPoolContextInfo_metaObject_00585e88[0];
    if (!g || ((g->_validity & 4) != 0) == false)
        FUN_002c0360();
    return g_igMemoryPoolContextInfo_metaObject_00585e88[0];
}
