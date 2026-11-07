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
int FUN_001c0ae0(float *, float, float);
void FUN_0027fa60(EnbayaDecoderView *, float, int, EnbayaKeyView **, EnbayaKeyView **);
void FUN_00192ab0(float *, EnbayaKeyView *, EnbayaKeyView *, float);
void FUN_00192cc0(float *, EnbayaKeyView *, EnbayaKeyView *, float);
void FUN_00192f00(float *, float *, float *, float);
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
    case 3: FUN_00192ab0(out, ka, kb, blend); break;
    case 1: FUN_00192cc0(out, ka, kb, blend); break;
    case 0: out[0] = kb->_quaternion[0]; out[1] = kb->_quaternion[1]; out[2] = kb->_quaternion[2]; out[3] = kb->_quaternion[3]; break;
    case 2: break;
    }
    return 1;
}
