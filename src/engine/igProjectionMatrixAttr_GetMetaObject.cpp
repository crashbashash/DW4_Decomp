#include "dw4/reflected.h"
extern igMetaObject *g_igProjectionMatrixAttr_metaObject[4];
extern "C" {
void FUN_001347c0(void);
igMetaObject *igProjectionMatrixAttr_GetMetaObject(void);
}
igMetaObject *igProjectionMatrixAttr_GetMetaObject(void)
{
    igMetaObject *g = g_igProjectionMatrixAttr_metaObject[0];
    bool t;
    if (!g || !(t = g->_validity & 4))
        FUN_001347c0();
    return g_igProjectionMatrixAttr_metaObject[0];
}
