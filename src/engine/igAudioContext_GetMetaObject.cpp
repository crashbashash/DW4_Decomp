#include "dw4/reflected.h"
extern igMetaObject *g_igAudioContext_metaObject[4];
extern "C" {
void FUN_00143010(void);
igMetaObject *igAudioContext_GetMetaObject(void);
}
igMetaObject *igAudioContext_GetMetaObject(void)
{
    igMetaObject *g = g_igAudioContext_metaObject[0];
    if (!g || ((g->_validity & 4) != 0) == false)
        FUN_00143010();
    return g_igAudioContext_metaObject[0];
}
