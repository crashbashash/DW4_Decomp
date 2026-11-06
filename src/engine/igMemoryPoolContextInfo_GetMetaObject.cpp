#include "dw4/reflected.h"
extern igMetaObject *g_igMemoryPoolContextInfo_metaObject_00585e88[4];
extern "C" {
void FUN_002c0360(void);
igMetaObject *igMemoryPoolContextInfo_GetMetaObject(void);
}
igMetaObject *igMemoryPoolContextInfo_GetMetaObject(void)
{
    igMetaObject *g = g_igMemoryPoolContextInfo_metaObject_00585e88[0];
    bool t;
    if (!g || !(t = g->_validity & 4))
        FUN_002c0360();
    return g_igMemoryPoolContextInfo_metaObject_00585e88[0];
}
