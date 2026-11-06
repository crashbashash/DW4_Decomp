#include "dw4/meta_object.h"
extern igMetaObject *g_igAudioContext_metaObject[4];
extern "C" {
void FUN_00143010(void);
igMetaObject *igAudioContext_GetMetaObject(void);
}
igMetaObject *igAudioContext_GetMetaObject(void)
{
    if (g_igAudioContext_metaObject[0] == 0 || igMetaObject_IsRegistered(g_igAudioContext_metaObject[0]) == false)
        FUN_00143010();
    return g_igAudioContext_metaObject[0];
}
