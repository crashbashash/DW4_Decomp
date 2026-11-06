#include "dw4/reflected.h"
extern igMetaObject *g_igAlphaStateAttr_metaObject[4];
extern "C" {
void FUN_0013b390(void);
igMetaObject *igAlphaStateAttr_GetMetaObject(void);
}
igMetaObject *igAlphaStateAttr_GetMetaObject(void)
{
    igMetaObject *g = g_igAlphaStateAttr_metaObject[0];
    if (!g || ((g->_validity & 4) != 0) == false)
        FUN_0013b390();
    return g_igAlphaStateAttr_metaObject[0];
}
