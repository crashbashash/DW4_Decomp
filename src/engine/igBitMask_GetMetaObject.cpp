#include "dw4/reflected.h"
extern igMetaObject *g_igBitMask_metaObject[4];
extern "C" {
void FUN_001a4e70(void);
igMetaObject *igBitMask_GetMetaObject(void);
}
igMetaObject *igBitMask_GetMetaObject(void)
{
    igMetaObject *g = g_igBitMask_metaObject[0];
    bool t;
    if (!g || !(t = g->_validity & 4))
        FUN_001a4e70();
    return g_igBitMask_metaObject[0];
}
