#include "dw4/reflected.h"
extern igMetaObject *g_igShadeModelAttr_metaObject[4];
extern "C" {
void FUN_00133a30(void);
igMetaObject *igShadeModelAttr_GetMetaObject(void);
}
igMetaObject *igShadeModelAttr_GetMetaObject(void)
{
    igMetaObject *g = g_igShadeModelAttr_metaObject[0];
    if (!g || ((g->_validity & 4) != 0) == false)
        FUN_00133a30();
    return g_igShadeModelAttr_metaObject[0];
}
