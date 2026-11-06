#include "dw4/reflected.h"
extern igMetaObject *g_igCullFaceAttr_metaObject[4];
extern "C" {
void FUN_001387b0(void);
igMetaObject *igCullFaceAttr_GetMetaObject(void);
}
igMetaObject *igCullFaceAttr_GetMetaObject(void)
{
    igMetaObject *g = g_igCullFaceAttr_metaObject[0];
    if (!g || ((g->_validity & 4) != 0) == false)
        FUN_001387b0();
    return g_igCullFaceAttr_metaObject[0];
}
