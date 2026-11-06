#include "dw4/reflected.h"
extern igMetaObject *g_igNormalizeNormalsStateAttr_metaObject[4];
extern "C" {
void FUN_00135090(void);
igMetaObject *igNormalizeNormalsStateAttr_GetMetaObject(void);
}
igMetaObject *igNormalizeNormalsStateAttr_GetMetaObject(void)
{
    igMetaObject *g = g_igNormalizeNormalsStateAttr_metaObject[0];
    if (!g || ((g->_validity & 4) != 0) == false)
        FUN_00135090();
    return g_igNormalizeNormalsStateAttr_metaObject[0];
}
