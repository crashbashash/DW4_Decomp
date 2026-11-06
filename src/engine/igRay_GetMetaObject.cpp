#include "dw4/reflected.h"
extern igMetaObject *g_igRay_metaObject[4];
extern "C" {
void FUN_00188340(void);
igMetaObject *igRay_GetMetaObject(void);
}
igMetaObject *igRay_GetMetaObject(void)
{
    igMetaObject *g = g_igRay_metaObject[0];
    bool t;
    if (!g || !(t = g->_validity & 4))
        FUN_00188340();
    return g_igRay_metaObject[0];
}
