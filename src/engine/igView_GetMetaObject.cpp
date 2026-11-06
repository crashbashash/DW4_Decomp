#include "dw4/reflected.h"
extern igMetaObject *g_igView_metaObject[4];
extern "C" {
void igView_EnsureRegistered(void);
igMetaObject *igView_GetMetaObject(void);
}
igMetaObject *igView_GetMetaObject(void)
{
    igMetaObject *g = g_igView_metaObject[0];
    if (!g || ((g->_validity & 4) != 0) == false)
        igView_EnsureRegistered();
    return g_igView_metaObject[0];
}
