#include "dw4/reflected.h"
extern igMetaObject *g_igShadeModelAttr_metaObject[4];
extern "C" {
void FUN_00133a30(void);
igMetaObject *igShadeModelAttr_GetMetaObject(void);
}
igMetaObject *igShadeModelAttr_GetMetaObject(void)
{
    igMetaObject *g = g_igShadeModelAttr_metaObject[0];
    bool t;
    if (!g || !(t = g->_validity & 4))
        FUN_00133a30();
    return g_igShadeModelAttr_metaObject[0];
}
