#include "dw4/reflected.h"
extern "C" long long FUN_00398e80(int, long long);
extern "C" int FUN_001dd4b0(long long, long long, long long *);
extern "C" void FUN_001af510(void *, long long);
extern "C" int FUN_003a7e90(void *, int *);
extern "C" void beAction2_StartComponents(void *, void *);
extern "C" int DAT_0050dfd8[4];
/* hypothesis: beAction2._insight points at a clock-carrying object with its 64-bit time at +80; igInsight is not reflected */
struct WcClock { char p[80]; long long time; };

/* matching construct: the reflected reference fields are 4-byte ints; the casts give the typed views (no layout effect) */
extern "C" void beAction2WAITCHECK_Update(beAction2 *arg0, beAction2InfoRam *arg1) {
    unsigned long long b;
    beAction2InfoWork *work;
    igAnimationState *obj;
    long long a;
    long long d;
    igAnimation *info;
    beAction2Info *ctx;
    igAnimationStateList *ew;
    work = (beAction2InfoWork *)arg1->_work;
    ctx = (beAction2Info *)arg1->_parentInfo;
    switch (work->_waitSt0) {
    case 1:
        if (FUN_003a7e90(arg1, &DAT_0050dfd8[0]) != 0) {
            work->_waitSt0 = 0;
            beAction2_StartComponents(arg0, arg1);
        }
        break;
    case 2:
        ew = (igAnimationStateList *)((igAnimationCombiner *)((int *)((igObjectList *)((igAnimationDatabase *)ctx->_animationDatabase)->_combinerList)->_data)[arg1->_ramNo])->_animationStateList;
        if (ew->_count == 1) {
            obj = (igAnimationState *)((int *)ew->_data)[0];
            info = (igAnimation *)obj->_animation;
            d = obj->_localTime - info->_keyFrameTimeOffset;
            b = info->_duration;
            a = info->_startTime;
            if (b != 0) {
                long long t;
                FUN_001dd4b0(d - a, b, &t);
                t += a;
            }
            FUN_001af510(obj, FUN_00398e80(arg1->_node, ((WcClock *)arg0->_insight)->time));
            if (b <= obj->_localTime) {
                work->_waitSt0 = 0;
                beAction2_StartComponents(arg0, arg1);
            }
        }
        break;
    case 3:
        if (work->_jointIsEnd != 0) {
            work->_waitSt0 = 0;
            beAction2_StartComponents(arg0, arg1);
        }
        break;
    }
}
