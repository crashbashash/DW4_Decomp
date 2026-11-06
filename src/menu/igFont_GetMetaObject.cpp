#include "dw4/reflected.h"
extern igMetaObject *g_igFont_metaObject[4];
extern "C" {
void igFont_EnsureRegistered(void);
igMetaObject *igFont_GetMetaObject(void);
}
igMetaObject *igFont_GetMetaObject(void)
{
    igMetaObject *g = g_igFont_metaObject[0];
    if (!g || ((g->_validity & 4) != 0) == false)
        igFont_EnsureRegistered();
    return g_igFont_metaObject[0];
}
