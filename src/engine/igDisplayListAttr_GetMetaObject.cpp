#include "dw4/reflected.h"
extern igMetaObject *g_igDisplayListAttr_metaObject[4];
extern "C" {
void FUN_00138160(void);
igMetaObject *igDisplayListAttr_GetMetaObject(void);
}
igMetaObject *igDisplayListAttr_GetMetaObject(void)
{
    igMetaObject *g = g_igDisplayListAttr_metaObject[0];
    bool t;
    if (!g || !(t = g->_validity & 4))
        FUN_00138160();
    return g_igDisplayListAttr_metaObject[0];
}
