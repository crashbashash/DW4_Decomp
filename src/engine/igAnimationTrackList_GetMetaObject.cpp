#include "dw4/reflected.h"
extern igMetaObject *g_igAnimationTrackList_metaObject[4];
extern "C" {
void FUN_001a9e70(void);
igMetaObject *igAnimationTrackList_GetMetaObject(void);
}
igMetaObject *igAnimationTrackList_GetMetaObject(void)
{
    igMetaObject *g = g_igAnimationTrackList_metaObject[0];
    bool t;
    if (!g || !(t = g->_validity & 4))
        FUN_001a9e70();
    return g_igAnimationTrackList_metaObject[0];
}
