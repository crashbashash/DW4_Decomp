#include "dw4/reflected.h"
extern igMetaObject *g_igRegistryValue_metaObject[4];
extern "C" {
void FUN_002bb670(void);
igMetaObject *igRegistryValue_GetMetaObject(void);
}
igMetaObject *igRegistryValue_GetMetaObject(void)
{
    igMetaObject *g = g_igRegistryValue_metaObject[0];
    if (!g || ((g->_validity & 4) != 0) == false)
        FUN_002bb670();
    return g_igRegistryValue_metaObject[0];
}
