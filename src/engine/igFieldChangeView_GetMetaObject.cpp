#include "dw4/reflected.h"
extern igMetaObject *g_igFieldChangeView_metaObject[4];
extern "C" {
void igFieldChangeView_EnsureRegistered(void);
igMetaObject *igFieldChangeView_GetMetaObject(void);
}
igMetaObject *igFieldChangeView_GetMetaObject(void)
{
    igMetaObject *g = g_igFieldChangeView_metaObject[0];
    if (!g || ((g->_validity & 4) != 0) == false)
        igFieldChangeView_EnsureRegistered();
    return g_igFieldChangeView_metaObject[0];
}
