#include "dw4/reflected.h"
extern igMetaObject *g_igAudioContext_metaObject[4];
extern "C" {
void FUN_00143010(void);
igMetaObject *igAudioContext_GetMetaObject(void);
}
igMetaObject *igAudioContext_GetMetaObject(void)
{
    igMetaObject *g = g_igAudioContext_metaObject[0];
    bool t;
    if (!g || !(t = g->_validity & 4))
        FUN_00143010();
    return g_igAudioContext_metaObject[0];
}
