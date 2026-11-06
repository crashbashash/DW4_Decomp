#include "dw4/reflected.h"
extern igMetaObject *g_igMemoryImage_metaObject[4];
extern "C" {
void FUN_0014de10(void);
igMetaObject *igMemoryImage_GetMetaObject(void);
}
igMetaObject *igMemoryImage_GetMetaObject(void)
{
    igMetaObject *g = g_igMemoryImage_metaObject[0];
    if (!g || ((g->_validity & 4) != 0) == false)
        FUN_0014de10();
    return g_igMemoryImage_metaObject[0];
}
