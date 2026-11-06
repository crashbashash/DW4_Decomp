#include "dw4/reflected.h"
extern igMetaObject *g_igMatrixOptStateAttr_metaObject[4];
extern "C" {
void FUN_00135ac0(void);
igMetaObject *igMatrixOptStateAttr_GetMetaObject(void);
}
igMetaObject *igMatrixOptStateAttr_GetMetaObject(void)
{
    igMetaObject *g = g_igMatrixOptStateAttr_metaObject[0];
    if (!g || ((g->_validity & 4) != 0) == false)
        FUN_00135ac0();
    return g_igMatrixOptStateAttr_metaObject[0];
}
