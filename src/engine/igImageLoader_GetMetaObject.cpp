#include "dw4/reflected.h"
extern igMetaObject *g_igImageLoader_metaObject[4];
extern "C" {
void FUN_0014da90(void);
igMetaObject *igImageLoader_GetMetaObject(void);
}
igMetaObject *igImageLoader_GetMetaObject(void)
{
    igMetaObject *g = g_igImageLoader_metaObject[0];
    if (!g || ((g->_validity & 4) != 0) == false)
        FUN_0014da90();
    return g_igImageLoader_metaObject[0];
}
