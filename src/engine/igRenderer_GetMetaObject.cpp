#include "dw4/reflected.h"
extern igMetaObject *g_igRenderer_metaObject[4];
extern "C" {
void igRenderer_EnsureRegistered(void);
igMetaObject *igRenderer_GetMetaObject(void);
}
igMetaObject *igRenderer_GetMetaObject(void)
{
    igMetaObject *g = g_igRenderer_metaObject[0];
    bool t;
    if (!g || !(t = g->_validity & 4))
        igRenderer_EnsureRegistered();
    return g_igRenderer_metaObject[0];
}
