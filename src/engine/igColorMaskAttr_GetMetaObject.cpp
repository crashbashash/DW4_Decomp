#include "dw4/reflected.h"
extern igMetaObject *g_igColorMaskAttr_metaObject[4];
extern "C" {
void FUN_00138d80(void);
igMetaObject *igColorMaskAttr_GetMetaObject(void);
}
igMetaObject *igColorMaskAttr_GetMetaObject(void)
{
    igMetaObject *g = g_igColorMaskAttr_metaObject[0];
    if (!g || ((g->_validity & 4) != 0) == false)
        FUN_00138d80();
    return g_igColorMaskAttr_metaObject[0];
}
