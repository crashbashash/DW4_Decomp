#include "dw4/reflected.h"
extern igMetaObject *g_igMatrixObjectPool_metaObject[4];
extern "C" {
void FUN_00199db0(void);
igMetaObject *igMatrixObjectPool_GetMetaObject(void);
}
igMetaObject *igMatrixObjectPool_GetMetaObject(void)
{
    igMetaObject *g = g_igMatrixObjectPool_metaObject[0];
    if (!g || ((g->_validity & 4) != 0) == false)
        FUN_00199db0();
    return g_igMatrixObjectPool_metaObject[0];
}
