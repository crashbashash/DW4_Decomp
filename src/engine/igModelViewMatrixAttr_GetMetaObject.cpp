#include "dw4/reflected.h"
extern igMetaObject *g_igModelViewMatrixAttr_metaObject[4];
extern "C" {
void FUN_001357e0(void);
igMetaObject *igModelViewMatrixAttr_GetMetaObject(void);
}
igMetaObject *igModelViewMatrixAttr_GetMetaObject(void)
{
    igMetaObject *g = g_igModelViewMatrixAttr_metaObject[0];
    if (!g || ((g->_validity & 4) != 0) == false)
        FUN_001357e0();
    return g_igModelViewMatrixAttr_metaObject[0];
}
