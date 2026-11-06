#include "dw4/reflected.h"
extern igMetaObject *g_igTransformRecorder_metaObject[4];
extern "C" {
void FUN_00195c00(void);
igMetaObject *igTransformRecorder_GetMetaObject(void);
}
igMetaObject *igTransformRecorder_GetMetaObject(void)
{
    igMetaObject *g = g_igTransformRecorder_metaObject[0];
    if (!g || ((g->_validity & 4) != 0) == false)
        FUN_00195c00();
    return g_igTransformRecorder_metaObject[0];
}
