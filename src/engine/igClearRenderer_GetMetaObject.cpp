#include "dw4/reflected.h"
extern igMetaObject *g_igClearRenderer_metaObject[4];
extern "C" {
void igClearRenderer_EnsureRegistered(void);
igMetaObject *igClearRenderer_GetMetaObject(void);
}
igMetaObject *igClearRenderer_GetMetaObject(void)
{
    igMetaObject *g = g_igClearRenderer_metaObject[0];
    if (!g || ((g->_validity & 4) != 0) == false)
        igClearRenderer_EnsureRegistered();
    return g_igClearRenderer_metaObject[0];
}
