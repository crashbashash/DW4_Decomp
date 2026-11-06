#include "dw4/reflected.h"
extern igMetaObject *g_igAppearance_metaObject[4];
extern "C" {
void FUN_001a6450(void);
igMetaObject *igAppearance_GetMetaObject(void);
}
igMetaObject *igAppearance_GetMetaObject(void)
{
    igMetaObject *g = g_igAppearance_metaObject[0];
    if (!g || ((g->_validity & 4) != 0) == false)
        FUN_001a6450();
    return g_igAppearance_metaObject[0];
}
