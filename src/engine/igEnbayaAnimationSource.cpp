extern "C" {
int FUN_00192810(...);
int Matrix44_SetTranslation(...);
}

class DW4VC_108_4 { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual void d24(); virtual int vX(int, int, int, int); };

class EnbayaSourceSlots24 {
public:
    virtual void pad0();
    virtual void pad1();
    virtual void pad2();
    virtual void pad3();
    virtual void pad4();
    virtual void pad5();
    virtual void pad6();
    virtual void pad7();
    virtual void pad8();
    virtual void pad9();
    virtual void pad10();
    virtual void pad11();
    virtual void pad12();
    virtual void pad13();
    virtual void pad14();
    virtual void pad15();
    virtual void pad16();
    virtual void pad17();
    virtual void pad18();
    virtual void pad19();
    virtual void pad20();
    virtual int f(int a, int b, int e);
};

class EnbayaSourceSlots26 {
public:
    virtual void pad0();
    virtual void pad1();
    virtual void pad2();
    virtual void pad3();
    virtual void pad4();
    virtual void pad5();
    virtual void pad6();
    virtual void pad7();
    virtual void pad8();
    virtual void pad9();
    virtual void pad10();
    virtual void pad11();
    virtual void pad12();
    virtual void pad13();
    virtual void pad14();
    virtual void pad15();
    virtual void pad16();
    virtual void pad17();
    virtual void pad18();
    virtual void pad19();
    virtual void pad20();
    virtual void pad21();
    virtual void pad22();
    virtual int f(int a, int b, int e);
};
class EnbayaSourceSlots28 {
public:
    virtual void pad0();
    virtual void pad1();
    virtual void pad2();
    virtual void pad3();
    virtual void pad4();
    virtual void pad5();
    virtual void pad6();
    virtual void pad7();
    virtual void pad8();
    virtual void pad9();
    virtual void pad10();
    virtual void pad11();
    virtual void pad12();
    virtual void pad13();
    virtual void pad14();
    virtual void pad15();
    virtual void pad16();
    virtual void pad17();
    virtual void pad18();
    virtual void pad19();
    virtual void pad20();
    virtual void pad21();
    virtual void pad22();
    virtual void pad23();
    virtual void pad24();
    virtual int f(int a, int b, int c, int g);
};

class EnbayaStreamSlots {
public:
    virtual void slot0();
    virtual void slot1();
    virtual void slot2();
    virtual void slot3();
    virtual float duration();
};
struct EnbayaSourceView {
    int _vtable; int _refCount; unsigned char _interpolationMethod[3]; unsigned char _drivenChannels; int _playMode;
    float _lastUpdateTimef; int _pad14; long long _lastUpdateTime; EnbayaStreamSlots *_enbayaAnimationStream;
};
struct EnbayaDecoderView { char _pad0[36]; float _interval; };
struct EnbayaKeyView { float _quaternion[4]; float _translation[4]; };

extern EnbayaDecoderView *DAT_00562720[4];
extern float DAT_005626e0[4];
extern "C" {
static int FUN_001c0ae0(float *, float, float);
void FUN_0027fa60(EnbayaDecoderView *, float, int, EnbayaKeyView **, EnbayaKeyView **);
void FUN_00192ab0(float *, float, EnbayaKeyView *, EnbayaKeyView *);
void FUN_00192cc0(float *, float, EnbayaKeyView *, EnbayaKeyView *);
void FUN_00192f00(float *, float *, float *, float);
}
extern "C" {
extern float DAT_005626e8[4];
extern float DAT_005626f0[4];
extern int DAT_005626f8[4];
extern float DAT_00562700[4];
}

extern "C" void Gap__Sg__igEnbayaAnimationSource__vfunc_13(void *arg0) {
    *(char *)((char *)(arg0) + 8) = 1;
    *(char *)((char *)(arg0) + 9) = 3;
    *(char *)((char *)(arg0) + 10) = 1;
}

extern "C" int Gap__Sg__igEnbayaAnimationSource__vfunc_23(void **arg0, int arg1, int arg2, int arg3) {
    int sp40[4];
    int sp30[4];
    int temp_s0;

    temp_s0 = ((DW4VC_108_4 *)(arg0))->vX((int)sp30, (int)sp40, (int)(arg2), (int)(arg3)) & 0xFF;
    FUN_00192810(sp30, arg1);
    Matrix44_SetTranslation(arg1, sp40);
    return temp_s0;
}

extern "C" int Gap__Sg__igEnbayaAnimationSource__vfunc_24(EnbayaSourceSlots24 *o, int a, int b, int c, int d, int e) {
    return o->f(a, b, e);
}

extern "C" int Gap__Sg__igEnbayaAnimationSource__vfunc_25(EnbayaSourceView *o, float *out, long long time, int track) {
    float blend;
    EnbayaKeyView *ka;
    EnbayaKeyView *kb;
    float duration;
    float t;
    EnbayaKeyView *a;
    EnbayaKeyView *b;
    EnbayaDecoderView *decoder;
    float r;
    if (o->_lastUpdateTime == time) {
        t = o->_lastUpdateTimef;
    } else {
        t = 0.00026214399258606136f * (float)(int)(time >> 18);
        duration = o->_enbayaAnimationStream->duration();
        if (duration <= 0.03333333507180214f) {
            duration = 0.05000000447034836f;
        }
        switch (o->_playMode) {
        case 4: duration += DAT_005626e0[0]; case 1: if (t > duration) { r = duration; } else if (t < 0.0f) { r = 0.0f; } else { FUN_001c0ae0(&r, t, duration); } break;
        case 3: case 0: FUN_001c0ae0(&r, t, duration); break;
        case 2: if (FUN_001c0ae0(&r, t, duration) & 1) { r = duration - r; } break;
        default: r = 0.0f; break;
        }
        t = r;
        o->_lastUpdateTimef = t;
        o->_lastUpdateTime = time;
    }
    decoder = DAT_00562720[0];
    a = 0;
    b = 0;
    FUN_0027fa60(decoder, t, track, &a, &b);
    ka = a;
    kb = b;
    blend = (t - ka->_translation[3]) / decoder->_interval;
    switch (o->_interpolationMethod[1]) {
    case 3: FUN_00192ab0(out, blend, ka, kb); break;
    case 1: FUN_00192cc0(out, blend, ka, kb); break;
    case 0: out[0] = kb->_quaternion[0]; out[1] = kb->_quaternion[1]; out[2] = kb->_quaternion[2]; out[3] = kb->_quaternion[3]; break;
    case 2: break;
    }
    return 1;
}

extern "C" {
static int FUN_001c0ae0(float *arg0, float fparg0, float fparg1) {
    float var_f1;
    int temp_f0;

    if (DAT_005626e8[0] == fparg0 && fparg1 == DAT_005626f0[0]) {
        *arg0 = DAT_00562700[0];
        return DAT_005626f8[0];
    }
    temp_f0 = (int)(fparg0 / fparg1);
    DAT_005626e8[0] = fparg0;
    var_f1 = fparg0 - ((float)temp_f0 * fparg1);
    DAT_005626f0[0] = fparg1;
    DAT_00562700[0] = var_f1;
    var_f1 = (var_f1 > 0.0f) ? var_f1 : 0.0f;
    DAT_00562700[0] = var_f1;
    *arg0 = var_f1;
    DAT_005626f8[0] = temp_f0;
    return temp_f0;
}
}

extern "C" int Gap__Sg__igEnbayaAnimationSource__vfunc_26(EnbayaSourceSlots26 *o, int a, int b, int c, int d, int e) {
    return o->f(a, b, e);
}

extern "C" int Gap__Sg__igEnbayaAnimationSource__vfunc_27(EnbayaSourceView *o, float *out, float *pos, long long time, int track) {
    float blend;
    float *ta;
    float *tb;
    EnbayaKeyView *ka;
    EnbayaKeyView *kb;
    float duration;
    float t;
    EnbayaKeyView *a;
    EnbayaKeyView *b;
    EnbayaDecoderView *decoder;
    float r;
    if (o->_lastUpdateTime == time) {
        t = o->_lastUpdateTimef;
    } else {
        t = 0.00026214399258606136f * (float)(int)(time >> 18);
        duration = o->_enbayaAnimationStream->duration();
        if (duration <= 0.03333333507180214f) {
            duration = 0.05000000447034836f;
        }
        switch (o->_playMode) {
        case 4: duration += DAT_005626e0[0]; case 1: if (t > duration) { r = duration; } else if (t < 0.0f) { r = 0.0f; } else { FUN_001c0ae0(&r, t, duration); } break;
        case 3: case 0: FUN_001c0ae0(&r, t, duration); break;
        case 2: if (FUN_001c0ae0(&r, t, duration) & 1) { r = duration - r; } break;
        default: r = 0.0f; break;
        }
        t = r;
        o->_lastUpdateTimef = t;
        o->_lastUpdateTime = time;
    }
    decoder = DAT_00562720[0];
    a = 0;
    b = 0;
    FUN_0027fa60(decoder, t, track, &a, &b);
    ka = a;
    kb = b;
    blend = (t - ka->_translation[3]) / decoder->_interval;
    ta = ka->_translation;
    tb = kb->_translation;
    switch (o->_interpolationMethod[0]) {
    case 1: FUN_00192f00(pos, ta, tb, blend); break;
    case 0: pos[0] = tb[0]; pos[1] = tb[1]; pos[2] = tb[2]; pos[3] = tb[3]; break;
    case 3: case 2: break;
    }
    switch (o->_interpolationMethod[1]) {
    case 3: FUN_00192ab0(out, blend, ka, kb); break;
    case 1: FUN_00192cc0(out, blend, ka, kb); break;
    case 0: out[0] = kb->_quaternion[0]; out[1] = kb->_quaternion[1]; out[2] = kb->_quaternion[2]; out[3] = kb->_quaternion[3]; break;
    case 2: break;
    }
    return 1;
}

extern "C" int Gap__Sg__igEnbayaAnimationSource__vfunc_28(EnbayaSourceSlots28 *o, int a, int b, int c, int d, int e, int g) {
    return o->f(a, b, c, g);
}
