#include "dw4/reflected.h"
extern igMetaObject *g_igTransformRecorder_metaObject[4];
extern "C" {
void FUN_00195c00(void);
igMetaObject *igTransformRecorder_GetMetaObject(void);
}
igMetaObject *igTransformRecorder_GetMetaObject(void)
{
    igMetaObject *g = g_igTransformRecorder_metaObject[0];
    bool t;
    if (!g || !(t = g->_validity & 4))
        FUN_00195c00();
    return g_igTransformRecorder_metaObject[0];
}
