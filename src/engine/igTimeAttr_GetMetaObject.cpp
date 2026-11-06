#include "dw4/reflected.h"
extern igMetaObject *g_igTimeAttr_metaObject[4];
extern "C" {
void FUN_00131040(void);
igMetaObject *igTimeAttr_GetMetaObject(void);
}
igMetaObject *igTimeAttr_GetMetaObject(void)
{
    igMetaObject *g = g_igTimeAttr_metaObject[0];
    bool t;
    if (!g || !(t = g->_validity & 4))
        FUN_00131040();
    return g_igTimeAttr_metaObject[0];
}
