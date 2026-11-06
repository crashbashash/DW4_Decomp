#include "dw4/reflected.h"
extern igMetaObject *g_igRenderer_metaObject[4];
extern "C" {
void igRenderer_EnsureRegistered(void);
igMetaObject *igRenderer_GetMetaObject(void);
}
igMetaObject *igRenderer_GetMetaObject(void)
{
    igMetaObject *g = g_igRenderer_metaObject[0];
    if (!g || ((g->_validity & 4) != 0) == false)
        igRenderer_EnsureRegistered();
    return g_igRenderer_metaObject[0];
}
