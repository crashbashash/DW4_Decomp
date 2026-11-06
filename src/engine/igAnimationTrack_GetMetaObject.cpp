#include "dw4/reflected.h"
extern igMetaObject *g_igAnimationTrack_metaObject[4];
extern "C" {
void FUN_001aa030(void);
igMetaObject *igAnimationTrack_GetMetaObject(void);
}
igMetaObject *igAnimationTrack_GetMetaObject(void)
{
    igMetaObject *g = g_igAnimationTrack_metaObject[0];
    bool t;
    if (!g || !(t = g->_validity & 4))
        FUN_001aa030();
    return g_igAnimationTrack_metaObject[0];
}
