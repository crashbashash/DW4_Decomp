#include "dw4/reflected.h"

typedef void (*TraversalFunction)(void);

extern "C" {
long long __fixsfdi(float);
float sqrtf(float);
float atan2f(float, float);
void *beNodeAnim_ResolveMetaObject(void);
void *beLoadingNode_ResolveMetaObject(void);
int igTraversal_RegisterFunction(int functionList, void *meta, TraversalFunction function);
void Gap__Core__igObject__vfunc_07(void *self);
void Gap__Core__igObject__vfunc_08__002ff0f0(void);
extern int DAT_00562640[4];
extern int g_bePadData_metaObject[4];

int beNodeAnim_Traverse(beNodeAnim *node, igCommonTraversal *trav);
void beNodeAnim_SetTime(beNodeAnim *node, long long time, long long now);
void bePadData_StickDirections(bePadData *pad, int *directions, float *stick);
}

#define CLOCK_TICK_SHIFT 18
#define NODE_ANIM_MAX_STEP_NS 33333333

extern "C" int beNodeAnim_TraversalFunction(igCommonTraversal *trav, beNodeAnim *node)
{
    return beNodeAnim_Traverse(node, trav);
}

/* Moves the time bias so that the clock reads `time` at the traversal clock `now`. */
extern "C" void beNodeAnim_SetTime(beNodeAnim *node, long long time, long long now)
{
    float scaled = (float)(unsigned int)(int)(now >> CLOCK_TICK_SHIFT);
    scaled = scaled * node->_timeScale;
    long long ticks = __fixsfdi(scaled);
    node->_timeBias = time - (ticks << CLOCK_TICK_SHIFT);
}

/* Advances the play clock to `now` and returns the node time, wrapped into the loop. */
extern "C" long long beNodeAnim_UpdateTime(beNodeAnim *node, long long now)
{
    float scaledTicks;
    const long long savedNow = now;
    long long loopEnd;
    long long time;

    time = node->_stopTime;
    switch (time) {
    default:
        break;
    case 0: {
        const long long play = node->_playTime;
        now = savedNow - node->_beforeTime;
        node->_playTime = now + play;
        if (NODE_ANIM_MAX_STEP_NS < now) {
            node->_timeBias = node->_timeBias - (now - NODE_ANIM_MAX_STEP_NS);
        }
        node->_beforeTime = savedNow;
        scaledTicks = (float)(unsigned int)(int)(savedNow >> CLOCK_TICK_SHIFT);
        scaledTicks = scaledTicks * node->_timeScale;
        time = __fixsfdi(scaledTicks);
        loopEnd = node->_loop2Time;
        time <<= CLOCK_TICK_SHIFT;
        time += node->_timeBias;
        if (time >= loopEnd) {
            if (loopEnd < time) {
                do {
                    time -= loopEnd;
                } while (loopEnd < time);
            }
            time += node->_loop1Time;
            beNodeAnim_SetTime(node, time, savedNow);
        }
    }
    }
    return time;
}

#undef NODE_ANIM_MAX_STEP_NS
#undef CLOCK_TICK_SHIFT

extern "C" void beNodeAnim_RegisterTraversalFunction(void)
{
    igTraversal_RegisterFunction(DAT_00562640[0], beNodeAnim_ResolveMetaObject(),
                                 (TraversalFunction)beNodeAnim_TraversalFunction);
}

extern "C" int beLoadingNode_TraversalFunction(igCommonTraversal *trav, beNodeAnim *node)
{
    return beNodeAnim_Traverse(node, trav);
}

extern "C" void beLoadingNode_Lock(beLoadingNode *node)
{
    node->_stopTime = node->_lockTime;
}

extern "C" int beLoadingNode_IsPastPlayLimit(beLoadingNode *node)
{
    return node->_playTime > node->_playLimitTime;
}

extern "C" void beLoadingNode_RegisterTraversalFunction(void)
{
    igTraversal_RegisterFunction(DAT_00562640[0], beLoadingNode_ResolveMetaObject(),
                                 (TraversalFunction)beLoadingNode_TraversalFunction);
}

extern "C" void Gap__Bec__bePadData__vfunc_07(bePadData *pad)
{
    Gap__Core__igObject__vfunc_07(pad);
    /* the dead zone is the length of the vector (0.4, 0) */
    pad->_enaLen = 0.4f;
    float x = pad->_enaLen;
    float y = 0.0f;
    float xx = x * x;
    pad->_enaLen = sqrtf(xx + y);
    pad->_adAngle = 0.7853982f;
    pad->_1sttime = 10;
    pad->_2ndtime = 6;
    pad->_lTime = 0; pad->_lLast = 0; pad->_lStk = 0; pad->_lRpt = 0; pad->_lTrg = 0;
    pad->_rTime = 0; pad->_rLast = 0; pad->_rStk = 0; pad->_rRpt = 0; pad->_rTrg = 0;
    pad->_rptime = 0; pad->_last = 0; pad->_repeat = 0; pad->_trigger = 0; pad->_button = 0;
}

extern "C" void Gap__Bec__bePadData__vfunc_08(void)
{
    Gap__Core__igObject__vfunc_08__002ff0f0();
}

/* Button edges and auto-repeat: the first repeat after _1sttime frames, then every _2ndtime. */
extern "C" void bePadData_UpdateButtons(bePadData *pad, int buttons)
{
    pad->_last = pad->_button;
    pad->_button = buttons;
    int held = pad->_button;
    pad->_trigger = held & (pad->_last ^ held);
    if ((pad->_last ^ pad->_button) != 0) {
        pad->_repeat = pad->_trigger;
        pad->_rptime = pad->_1sttime;
        return;
    }
    int wait = pad->_rptime - 1;
    pad->_rptime = wait;
    if (wait != 0) {
        pad->_repeat = 0;
        return;
    }
    pad->_repeat = pad->_button;
    pad->_rptime = pad->_2ndtime;
}

extern "C" void bePadData_UpdateLeftStick(bePadData *pad, float *stick)
{
    float view[2];
    pad->_LStick[0] = stick[0];
    pad->_LStick[1] = stick[1];
    pad->_lLast = pad->_lStk;
    view[0] = pad->_LStick[0];
    view[1] = pad->_LStick[1];
    bePadData_StickDirections(pad, &pad->_lStk, view);
    pad->_lTrg = pad->_lStk & (pad->_lLast ^ pad->_lStk);
    if ((pad->_lLast ^ pad->_lStk) != 0) {
        pad->_lRpt = pad->_lTrg;
        pad->_lTime = pad->_1sttime;
    } else {
        if (--pad->_lTime != 0) {
            pad->_lRpt = 0;
        } else {
            pad->_lRpt = pad->_lStk;
            pad->_lTime = pad->_2ndtime;
        }
    }
}

extern "C" void bePadData_UpdateRightStick(bePadData *pad, float *stick)
{
    float view[2];
    pad->_RStick[0] = stick[0];
    pad->_RStick[1] = stick[1];
    pad->_rLast = pad->_rStk;
    view[0] = pad->_RStick[0];
    view[1] = pad->_RStick[1];
    bePadData_StickDirections(pad, &pad->_rStk, view);
    int held = pad->_rStk;
    pad->_rTrg = held & (pad->_rLast ^ held);
    if ((pad->_rLast ^ pad->_rStk) != 0) {
        pad->_rRpt = pad->_rTrg;
        pad->_rTime = pad->_1sttime;
        return;
    }
    int wait = pad->_rTime - 1;
    pad->_rTime = wait;
    if (wait != 0) {
        pad->_rRpt = 0;
        return;
    }
    pad->_rRpt = pad->_rStk;
    pad->_rTime = pad->_2ndtime;
}

/* Stick vector to direction bits (8 left, 4 down, 2 right, 1 up): a quadrant widened by half of
 * _adAngle on each side, nothing inside the _enaLen dead zone. */
extern "C" void bePadData_StickDirections(bePadData *pad, int *directions, float *stick)
{
    const float *view = stick;
    float length;
    float angle;
    float half;
    float y, x;
    x = view[0];
    y = view[1];
    length = sqrtf(x * x + y * y);
    angle = atan2f(stick[1], stick[0]);
    half = 0.5f * pad->_adAngle;
    *directions = 0;
    if (!(length < pad->_enaLen)) {
        if (angle < -2.3561945f + half) {
            *directions |= 8;
        }
        if (!(angle < -2.3561945f - half) && (angle <= -0.7853982f + half)) {
            *directions |= 4;
        }
        if (!(angle <= -0.7853982f - half) && (angle < 0.7853982f + half)) {
            *directions |= 2;
        }
        if (!(angle < 0.7853982f - half) && (angle <= 2.3561945f + half)) {
            *directions |= 1;
        }
        if (!(angle <= 2.3561945f - half)) {
            *directions |= 8;
        }
    }
}

extern "C" int Gap__Bec__bePadData__vfunc_20(void)
{
    return g_bePadData_metaObject[0];
}
