#include "dw4/reflected.h"
extern igMetaObject *g_igMatrixObjectList_metaObject[4];
extern "C" {
void FUN_001e4bc0(void);
igMetaObject *igMatrixObjectList_GetMetaObject(void);
}
igMetaObject *igMatrixObjectList_GetMetaObject(void)
{
    igMetaObject *g = g_igMatrixObjectList_metaObject[0];
    if (!g || ((g->_validity & 4) != 0) == false)
        FUN_001e4bc0();
    return g_igMatrixObjectList_metaObject[0];
}
