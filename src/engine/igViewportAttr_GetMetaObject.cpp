#include "dw4/reflected.h"
extern igMetaObject *g_igViewportAttr_metaObject[4];
extern "C" {
void FUN_00130570(void);
igMetaObject *igViewportAttr_GetMetaObject(void);
}
igMetaObject *igViewportAttr_GetMetaObject(void)
{
    igMetaObject *g = g_igViewportAttr_metaObject[0];
    bool t;
    if (!g || !(t = g->_validity & 4))
        FUN_00130570();
    return g_igViewportAttr_metaObject[0];
}
