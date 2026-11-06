#include "dw4/reflected.h"
extern igMetaObject *g_igMatrixObject_metaObject[4];
extern "C" {
void FUN_001e4d30(void);
igMetaObject *igMatrixObject_GetMetaObject(void);
}
igMetaObject *igMatrixObject_GetMetaObject(void)
{
    igMetaObject *g = g_igMatrixObject_metaObject[0];
    if (!g || ((g->_validity & 4) != 0) == false)
        FUN_001e4d30();
    return g_igMatrixObject_metaObject[0];
}
