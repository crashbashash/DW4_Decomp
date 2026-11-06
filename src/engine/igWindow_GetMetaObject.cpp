#include "dw4/reflected.h"
extern igMetaObject *g_igWindow_metaObject[4];
extern "C" {
void FUN_00145de0(void);
igMetaObject *igWindow_GetMetaObject(void);
}
igMetaObject *igWindow_GetMetaObject(void)
{
    igMetaObject *g = g_igWindow_metaObject[0];
    bool t;
    if (!g || !(t = g->_validity & 4))
        FUN_00145de0();
    return g_igWindow_metaObject[0];
}
