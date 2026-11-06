#include "dw4/reflected.h"
extern igMetaObject *g_igPixelPipelineModeAttr_metaObject[4];
extern "C" {
void FUN_00134c30(void);
igMetaObject *igPixelPipelineModeAttr_GetMetaObject(void);
}
igMetaObject *igPixelPipelineModeAttr_GetMetaObject(void)
{
    igMetaObject *g = g_igPixelPipelineModeAttr_metaObject[0];
    if (!g || ((g->_validity & 4) != 0) == false)
        FUN_00134c30();
    return g_igPixelPipelineModeAttr_metaObject[0];
}
