#include "dw4/reflected.h"
extern igMetaObject *g_igMessageFilter_metaObject[4];
extern "C" {
void FUN_00231cb0(void);
igMetaObject *igMessageFilter_GetMetaObject(void);
}
igMetaObject *igMessageFilter_GetMetaObject(void)
{
    igMetaObject *g = g_igMessageFilter_metaObject[0];
    bool t;
    if (!g || !(t = g->_validity & 4))
        FUN_00231cb0();
    return g_igMessageFilter_metaObject[0];
}
