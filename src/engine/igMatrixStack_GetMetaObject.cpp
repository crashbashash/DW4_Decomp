#include "dw4/reflected.h"
extern igMetaObject *g_igMatrixStack_metaObject[4];
extern "C" {
void FUN_001e4820(void);
igMetaObject *igMatrixStack_GetMetaObject(void);
}
igMetaObject *igMatrixStack_GetMetaObject(void)
{
    igMetaObject *g = g_igMatrixStack_metaObject[0];
    if (!g || ((g->_validity & 4) != 0) == false)
        FUN_001e4820();
    return g_igMatrixStack_metaObject[0];
}
