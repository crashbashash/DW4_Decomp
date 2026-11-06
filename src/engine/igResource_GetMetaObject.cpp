#include "dw4/reflected.h"
extern igMetaObject *g_igResource_metaObject[4];
extern "C" {
void FUN_002bad40(void);
igMetaObject *igResource_GetMetaObject(void);
}
igMetaObject *igResource_GetMetaObject(void)
{
    igMetaObject *g = g_igResource_metaObject[0];
    if (!g || ((g->_validity & 4) != 0) == false)
        FUN_002bad40();
    return g_igResource_metaObject[0];
}
