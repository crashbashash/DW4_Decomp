#include "dw4/reflected.h"
extern igMetaObject *g_igProjectionMatrixAttrPool_metaObject[4];
extern "C" {
void FUN_0019a200(void);
igMetaObject *igProjectionMatrixAttrPool_GetMetaObject(void);
}
igMetaObject *igProjectionMatrixAttrPool_GetMetaObject(void)
{
    igMetaObject *g = g_igProjectionMatrixAttrPool_metaObject[0];
    bool t;
    if (!g || !(t = g->_validity & 4))
        FUN_0019a200();
    return g_igProjectionMatrixAttrPool_metaObject[0];
}
