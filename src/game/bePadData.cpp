#include "dw4/reflected.h"

extern "C" int FUN_0039ab20(...);
extern "C" int FUN_0039a930(void *node, void *traversal);
extern "C" long long __fixsfdi(float);
extern "C" int FUN_001e06c0(int, int, void (*)(void));
extern "C" int FUN_0034e870(...);
extern "C" void FUN_0039ad80(void);
extern "C" int FUN_0034e5d0(...);
extern "C" void FUN_0039ae10(void);
extern "C" float sqrtf(float);
extern "C" void Gap__Core__igObject__vfunc_07(void *);
extern "C" void Gap__Bec__bePadData__vfunc_07(void *self);
extern "C" void Gap__Core__igObject__vfunc_08__002ff0f0(void);
extern "C" void Gap__Bec__bePadData__vfunc_08(void);
extern "C" float atan2f(float, float);
extern "C" int Gap__Bec__bePadData__vfunc_20(void);
extern "C" void FUN_0039a960(beNodeAnim *arg0, long long arg1, long long arg2);
extern "C" long long FUN_0039a9e0(beNodeAnim *self, long long elapsed);
extern "C" int DAT_00562640[4];
extern "C" int FUN_0039adc0(igCommonTraversal *traversal, beNodeAnim *node);
extern "C" void FUN_0039adf0(beLoadingNode *arg0);
extern "C" int FUN_0039ae00(beLoadingNode *arg0);
extern "C" void FUN_0039af10(bePadData *arg0, int arg1);
struct V2 { float x; float y; };
struct O { char pad[12]; float f12; float f16; char pad2[8]; int f28; int f32; int f36; int f40; int f44; char pad3[48]; int f96; int f100; };
extern "C" void FUN_0039af90(struct O *arg0, struct V2 *arg1);
struct Q { char p0[20]; float f20; float f24; char p1[20]; int f48; int f52; int f56; int f60; int f64; char p2[28]; int f96; int f100; };
extern "C" void FUN_0039b050(struct Q *arg0, float *arg1);
extern "C" void FUN_0039b110(bePadData *arg0, int *arg1, float *arg2);
extern "C" int g_bePadData_metaObject[4];

int FUN_0039a930(void *node, void *traversal) {
    return FUN_0039ab20(traversal, node);
}

void FUN_0039a960(beNodeAnim *arg0, long long arg1, long long arg2) {
    long long r;
    float f;
    f = (float)(unsigned int)(int)(arg2 >> 0x12);
    f = f * arg0->_timeScale;
    r = __fixsfdi(f);
    arg0->_timeBias = arg1 - (r << 0x12);
}

#define CLOCK_TICK_SHIFT 18
#define NODE_ANIM_MAX_STEP_NS 33333333
long long FUN_0039a9e0(beNodeAnim *self, long long elapsed) {
    float scaledTicks;
    const long long savedNow = elapsed;
    long long loopEnd;
    long long result;

    result = self->_stopTime;
    switch (result) {
    default:
        break;
    case 0: {
        const long long play = self->_playTime;
        elapsed = savedNow - self->_beforeTime;
        self->_playTime = elapsed + play;
        if (NODE_ANIM_MAX_STEP_NS < elapsed) {
            self->_timeBias = self->_timeBias - (elapsed - NODE_ANIM_MAX_STEP_NS);
        }
        self->_beforeTime = savedNow;
        scaledTicks = (float)(unsigned int)(int)(savedNow >> CLOCK_TICK_SHIFT);
        scaledTicks = scaledTicks * self->_timeScale;
        result = __fixsfdi(scaledTicks);
        loopEnd = self->_loop2Time;
        result <<= CLOCK_TICK_SHIFT;
        result += self->_timeBias;
        if (result >= loopEnd) {
            if (loopEnd < result) {
                do {
                    result -= loopEnd;
                } while (loopEnd < result);
            }
            result += self->_loop1Time;
            FUN_0039a960(self, result, savedNow);
        }
    }
    }
    return result;
}

#undef NODE_ANIM_MAX_STEP_NS
#undef CLOCK_TICK_SHIFT

void FUN_0039ad80(void) {
    FUN_001e06c0(DAT_00562640[0], FUN_0034e870(), (void (*)())FUN_0039a930);
}

int FUN_0039adc0(igCommonTraversal *traversal, beNodeAnim *node)
{
    return FUN_0039ab20(node, traversal);
}

void FUN_0039adf0(beLoadingNode *arg0) {
    arg0->_stopTime = arg0->_lockTime;
}

int FUN_0039ae00(beLoadingNode *arg0) {
    return arg0->_playTime > arg0->_playLimitTime;
}

void FUN_0039ae10(void) {
    FUN_001e06c0(DAT_00562640[0], FUN_0034e5d0(), (void (*)())FUN_0039adc0);
}

void Gap__Bec__bePadData__vfunc_07(void *self) {
    bePadData *p = (bePadData *)self;
    Gap__Core__igObject__vfunc_07(self);
    /* matching construct: the store/reload and sqrtf(x*x+0) reproduce the retail instruction sequence */
    p->_enaLen = 0.4f; float x = p->_enaLen; float z = 0.0f; float s = x * x; p->_enaLen = sqrtf(s + z);
    p->_adAngle = 0.7853982f;
    p->_1sttime = 10;
    p->_2ndtime = 6;
    p->_lTime = 0; p->_lLast = 0; p->_lStk = 0; p->_lRpt = 0; p->_lTrg = 0;
    p->_rTime = 0; p->_rLast = 0; p->_rStk = 0; p->_rRpt = 0; p->_rTrg = 0;
    p->_rptime = 0; p->_last = 0; p->_repeat = 0; p->_trigger = 0; p->_button = 0;
}

void Gap__Bec__bePadData__vfunc_08(void)
{
    Gap__Core__igObject__vfunc_08__002ff0f0();
}

/* Pad edge detection and auto-repeat; arg0 is the pad data and arg1 is the new button word. */
void FUN_0039af10(bePadData *arg0, int arg1) {
    int temp_a1;
    int temp_v1;
    int var_v1;

    arg0->_last = arg0->_button;
    arg0->_button = arg1;
    temp_a1 = arg0->_button;
    arg0->_trigger = temp_a1 & (arg0->_last ^ temp_a1);
    if ((arg0->_last ^ arg0->_button) != 0) {
        arg0->_repeat = arg0->_trigger;
        arg0->_rptime = arg0->_1sttime;
        return;
    }
    temp_v1 = arg0->_rptime - 1;
    arg0->_rptime = temp_v1;
    if (temp_v1 != 0) {
        arg0->_repeat = 0;
        return;
    }
    arg0->_repeat = arg0->_button;
    arg0->_rptime = arg0->_2ndtime;
}

void FUN_0039af90(struct O *arg0, struct V2 *arg1) {
    struct V2 v;
    arg0->f12 = arg1->x;
    arg0->f16 = arg1->y;
    arg0->f40 = arg0->f36;
    v.x = arg0->f12;
    v.y = arg0->f16;
    FUN_0039b110((bePadData *)arg0, &arg0->f36, (float *)&v);
    arg0->f28 = arg0->f36 & (arg0->f40 ^ arg0->f36);
    if ((arg0->f40 ^ arg0->f36) != 0) {
        arg0->f32 = arg0->f28;
        arg0->f44 = arg0->f96;
    } else {
        if (--arg0->f44 != 0) {
            arg0->f32 = 0;
        } else {
            arg0->f32 = arg0->f36;
            arg0->f44 = arg0->f100;
        }
    }
}

void FUN_0039b050(struct Q *arg0, float *arg1) {
    float sp28[2];
    int a;
    int v;
    arg0->f20 = arg1[0];
    arg0->f24 = arg1[1];
    arg0->f60 = arg0->f56;
    sp28[0] = arg0->f20;
    sp28[1] = arg0->f24;
    FUN_0039b110((bePadData *)arg0, &arg0->f56, sp28);
    a = arg0->f56;
    arg0->f48 = a & (arg0->f60 ^ a);
    if ((arg0->f60 ^ arg0->f56) != 0) {
        arg0->f52 = arg0->f48;
        arg0->f64 = arg0->f96;
        return;
    }
    v = arg0->f64 - 1;
    arg0->f64 = v;
    if (v != 0) {
        arg0->f52 = 0;
        return;
    }
    arg0->f52 = arg0->f56;
    arg0->f64 = arg0->f100;
}

void FUN_0039b110(bePadData *arg0, int *arg1, float *arg2) {
    const float *view = arg2;
    float d;
    float ang;
    float half;
    float y, x;
    x = view[0];
    y = view[1];
    d = sqrtf(x * x + y * y);
    ang = atan2f(arg2[1], arg2[0]);
    half = 0.5f * arg0->_adAngle;
    *arg1 = 0;
    if (!(d < arg0->_enaLen)) {
        if (ang < -2.3561945f + half) {
            *arg1 |= 8;
        }
        if (!(ang < -2.3561945f - half) && (ang <= -0.7853982f + half)) {
            *arg1 |= 4;
        }
        if (!(ang <= -0.7853982f - half) && (ang < 0.7853982f + half)) {
            *arg1 |= 2;
        }
        if (!(ang < 0.7853982f - half) && (ang <= 2.3561945f + half)) {
            *arg1 |= 1;
        }
        if (!(ang <= 2.3561945f - half)) {
            *arg1 |= 8;
        }
    }
}

int Gap__Bec__bePadData__vfunc_20(void)
{
    return g_bePadData_metaObject[0];
}
