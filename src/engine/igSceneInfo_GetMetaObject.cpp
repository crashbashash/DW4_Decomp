#include "dw4/reflected.h"
extern igMetaObject *g_igSceneInfo_metaObject[4];
extern "C" {
void FUN_0019b270(void);
igMetaObject *igSceneInfo_GetMetaObject(void);
}
igMetaObject *igSceneInfo_GetMetaObject(void)
{
    igMetaObject *g = g_igSceneInfo_metaObject[0];
    if (!g || ((g->_validity & 4) != 0) == false)
        FUN_0019b270();
    return g_igSceneInfo_metaObject[0];
}
