#include "dw4/reflected.h"
int FUN_001c1560();
int FUN_0027ef50(int, int, unsigned char);
int FUN_002808f0();
int igObject_IsKindOf();
extern int DAT_00561b48[4];
extern int DAT_00562718[4];
extern unsigned char GPR_00554b94;

void Gap__Sg__igEnbayaAnimationState__vfunc_23(igEnbayaAnimationState *arg0) {
    int found;
    int i;
    igAnimationTrackList *l;
    int n;
    igAnimationTrack *e;
    igEnbayaTransformSource *c;
    found = 0;
    l = (igAnimationTrackList *)((igAnimation *)arg0->_animation)->_trackList;
    n = l->_count;
    for (i = 0; i < n; i++) {
        e = (igAnimationTrack *)((int *)l->_data)[i];
        if (e != 0 && (c = (igEnbayaTransformSource *)e->_source) != 0 && igObject_IsKindOf(c, DAT_00561b48[0]) != 0) {
            found = ((igEnbayaAnimationSource *)c->_enbayaAnimationSource)->_enbayaAnimationStream;
            break;
        }
    }
    if (found != 0) {
        arg0->_context = FUN_001c1560(DAT_00562718[0], ((igAnimationTrackList *)((igAnimation *)arg0->_animation)->_trackList)->_count);
        if (GPR_00554b94 == 0) {
            arg0->_fastCacheDecodingState = 0;
        }
        FUN_0027ef50(arg0->_context, FUN_002808f0(found), arg0->_fastCacheDecodingState);
    }
}
