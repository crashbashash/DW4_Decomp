#include "dw4/reflected.h"
extern igMetaObject *g_igProjectionMatrixAttrPool_metaObject[4];
extern "C" {
void FUN_0019a200(void);
igMetaObject *igProjectionMatrixAttrPool_GetMetaObject(void);
}
igMetaObject *igProjectionMatrixAttrPool_GetMetaObject(void)
{
    igMetaObject *g = g_igProjectionMatrixAttrPool_metaObject[0];
    if (!g || ((g->_validity & 4) != 0) == false)
        FUN_0019a200();
    return g_igProjectionMatrixAttrPool_metaObject[0];
}
