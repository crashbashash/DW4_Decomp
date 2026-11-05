#include "dw4/reflected.h"
extern "C" {
extern int DAT_004e0858[4];
extern int DAT_00561b48[4];
extern int DAT_00585be0[4];
long long FUN_00230110(float);
void *igProperty_FindByName(...);
int FUN_001ac140(void *, long long);
int FUN_001ae660(void *, void *, int, int, int, int *, int, long long, float, float, int);
int FUN_001ae780(...);
int igObject_IsKindOf(...);
long long FUN_00398e80(int, long long);
int beAction2MOTIONSET_Start(beAction2 *arg0, beAction2InfoRam *arg1, beAction2MOTIONSET *arg2) {
    beAction2Info *info = (beAction2Info *)arg1->_parentInfo;
    beAction2InfoWork *work = (beAction2InfoWork *)arg1->_work;
    int names = ((igAnimationDatabase *)info->_animationDatabase)->_animationList;
    int name = arg2->_name;
    int nameOrEmpty;
    if (name != 0) nameOrEmpty = name; else nameOrEmpty = (int)DAT_004e0858;
    igAnimation *res = (igAnimation *)igProperty_FindByName(names, DAT_00585be0[0], nameOrEmpty);
    igAnimationCombiner *anim = ((igAnimationCombiner **)((igAnimationCombinerList *)((igAnimationDatabase *)info->_animationDatabase)->_combinerList)->_data)[arg1->_ramNo];
    long long biasOld;
    float zero = 0.0f;
    float blend;
    long long hokanTicks;
    if (work->_isNoHokan != 0 || arg2->_hokanTime == 0.0f) {
        blend = 1.0f;
        work->_isNoHokan = 0;
        hokanTicks = 1;
    } else {
        hokanTicks = FUN_00230110(1e9f * arg2->_hokanTime / 60.0f);
        blend = 0.0f;
    }
    if (((igAnimationStateList *)anim->_animationStateList)->_count >= 2) FUN_001ae780(anim, 0);
    int value = res->_priority;
    FUN_001ae660(anim, res, 1, 1, 1, &value, 0, hokanTicks, blend, 1.0f, 0);
    long long cur = FUN_00398e80(arg1->_node, ((igInsightCore *)arg0->_insight)->_worldTime);
    FUN_001ac140(anim, cur);
    if (((char *)arg2->_hokanMode)[0] == 'S') {
        igAnimationState *tr = ((igAnimationState **)((igAnimationStateList *)anim->_animationStateList)->_data)[0];
        float f = (float)(unsigned int)(int)(((igInsightCore *)arg0->_insight)->_worldTime >> 18);
        long long ticks = FUN_00230110(f * tr->_timeScale);
        biasOld = tr->_timeBias;
        tr->_timeBias = (ticks << 18) + biasOld;
        tr->_timeBias -= FUN_00230110(f * zero) << 18;
        tr->_timeScale = zero;
    }
    if (((char *)arg2->_hokanMode)[1] == 'S') {
        igAnimationStateList *sl = (igAnimationStateList *)anim->_animationStateList;
        int idx = sl->_count - 1;
        igAnimationState *tr = ((igAnimationState **)sl->_data)[idx];
        float f = (float)(unsigned int)(int)(((igInsightCore *)arg0->_insight)->_worldTime >> 18);
        long long ticks = FUN_00230110(f * tr->_timeScale);
        biasOld = tr->_timeBias;
        tr->_timeBias = (ticks << 18) + biasOld;
        tr->_timeBias -= FUN_00230110(f * zero) << 18;
        tr->_timeScale = zero;
    }
    igAnimationTrackList *bl = (igAnimationTrackList *)res->_trackList;
    int isLoop = ((char *)arg2->_loopMode)[0] == 'L';
    int j;
    for (j = 0; j < bl->_count; j++) {
        void *tg = (void *)((igAnimationTrack **)bl->_data)[j]->_source;
        if (tg != 0) {
            if (igObject_IsKindOf(tg, DAT_00561b48[0]) != 0) {
                igEnbayaAnimationSource *m = (igEnbayaAnimationSource *)((igEnbayaTransformSource *)tg)->_enbayaAnimationSource;
                if (isLoop) m->_playMode = 0; else m->_playMode = 4;
                break;
            } else if (isLoop) {
                igCompressedAnimationSequenceQS *sq = (igCompressedAnimationSequenceQS *)tg;
                if (sq->_playMode == 3) break;
                sq->_playMode = 3;
            } else {
                igCompressedAnimationSequenceQS *sq = (igCompressedAnimationSequenceQS *)tg;
                if (sq->_playMode == 1) break;
                sq->_playMode = 1;
            }
        }
    }
    work->_motionSt0 = 1;
    work->_isMotion = 1;
    return 1;
}
}
