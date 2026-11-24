void FUN_001c07d0(void) {
    thunk_Enbaya_InitMemoryManagement(0);
}

void FUN_001c07e0(void) {

}

namespace Gap {
namespace Sg {

void igEnbayaAnimationSource::resetFields(int flag)
{
    _interpolationMethod[0] = 1;
    _interpolationMethod[1] = 3;
    _interpolationMethod[2] = 1;
}

bool igEnbayaAnimationSource::getMatrix(igMatrix44f &matrix, long long time, int trackId)
{
    float translation[4];
    float quaternion[4];
    bool result = evaluateRotationAndTranslation(quaternion, translation, time, trackId);
    FUN_00192810((const float *)quaternion, (float *)&matrix);
    igMatrix44f_SetTranslation((float *)&matrix, translation);
    return result;
}

bool igEnbayaAnimationSource::getMatrix(igMatrix44f &matrix, long long time, int *cachedLastTimeFrame, int flags, int trackId)
{
    return getMatrix(matrix, time, trackId);
}
}
}

float g_enbayaPlayOnceEndOffset;

namespace Gap {
namespace Sg {

bool igEnbayaAnimationSource::evaluateRotation(float *quaternion, long long time, int trackId)
{
    float blend;
    EnbayaKeyView *ka;
    EnbayaKeyView *kb;
    float duration;
    float t;
    EnbayaKeyView *a;
    EnbayaKeyView *b;
    EnbayaDecoderView *decoder;
    float r;
    if (_lastUpdateTime == time) {
        t = _lastUpdateTimef;
    } else {
        t = 0.00026214399258606136f * (float)(int)(time >> 18);
        duration = ((EnbayaStreamSlots *)_enbayaAnimationStream)->duration();
        if (duration <= 0.03333333507180214f) {
            duration = 0.05000000447034836f;
        }
        switch (_playMode) {
        case 4: duration += g_enbayaPlayOnceEndOffset; case 1: if (t > duration) { r = duration; } else if (t < 0.0f) { r = 0.0f; } else { FUN_001c0ae0(&r, t, duration); } break;
        case 3: case 0: FUN_001c0ae0(&r, t, duration); break;
        case 2: if (FUN_001c0ae0(&r, t, duration) & 1) { r = duration - r; } break;
        default: r = 0.0f; break;
        }
        t = r;
        _lastUpdateTimef = t;
        _lastUpdateTime = time;
    }
    decoder = ((EnbayaDecoderView * *)DAT_00562720)[0];
    a = 0;
    b = 0;
    FUN_0027fa60((EnbayaContext *)decoder, t, trackId, (EnbayaSlot **)&a, (EnbayaSlot **)&b);
    ka = a;
    kb = b;
    blend = (t - ka->_translation[3]) / decoder->_interval;
    switch (_interpolationMethod[1]) {
    case 3: FUN_00192ab0(quaternion, blend, (void *)ka, (void *)kb); break;
    case 1: Quaternion_Lerp(quaternion, blend, (const float *)ka, (const float *)kb); break;
    case 0: quaternion[0] = kb->_quaternion[0]; quaternion[1] = kb->_quaternion[1]; quaternion[2] = kb->_quaternion[2]; quaternion[3] = kb->_quaternion[3]; break;
    case 2: break;
    }
    return 1;
}
}
}

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

namespace Gap {
namespace Sg {

bool igEnbayaAnimationSource::evaluateRotation(float *quaternion, long long time, int *cachedLastTimeFrame, int flags, int trackId)
{
    return evaluateRotation(quaternion, time, trackId);
}

bool igEnbayaAnimationSource::evaluateRotationAndTranslation(float *quaternion, float *translation, long long time, int trackId)
{
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
    if (_lastUpdateTime == time) {
        t = _lastUpdateTimef;
    } else {
        t = 0.00026214399258606136f * (float)(int)(time >> 18);
        duration = ((EnbayaStreamSlots *)_enbayaAnimationStream)->duration();
        if (duration <= 0.03333333507180214f) {
            duration = 0.05000000447034836f;
        }
        switch (_playMode) {
        case 4: duration += g_enbayaPlayOnceEndOffset; case 1: if (t > duration) { r = duration; } else if (t < 0.0f) { r = 0.0f; } else { FUN_001c0ae0(&r, t, duration); } break;
        case 3: case 0: FUN_001c0ae0(&r, t, duration); break;
        case 2: if (FUN_001c0ae0(&r, t, duration) & 1) { r = duration - r; } break;
        default: r = 0.0f; break;
        }
        t = r;
        _lastUpdateTimef = t;
        _lastUpdateTime = time;
    }
    decoder = ((EnbayaDecoderView * *)DAT_00562720)[0];
    a = 0;
    b = 0;
    FUN_0027fa60((EnbayaContext *)decoder, t, trackId, (EnbayaSlot **)&a, (EnbayaSlot **)&b);
    ka = a;
    kb = b;
    blend = (t - ka->_translation[3]) / decoder->_interval;
    ta = ka->_translation;
    tb = kb->_translation;
    switch (_interpolationMethod[0]) {
    case 1: Vec3_Lerp(translation, blend, (const float *)ta, (const float *)tb); break;
    case 0: translation[0] = tb[0]; translation[1] = tb[1]; translation[2] = tb[2]; translation[3] = tb[3]; break;
    case 3: case 2: break;
    }
    switch (_interpolationMethod[1]) {
    case 3: FUN_00192ab0(quaternion, blend, (void *)ka, (void *)kb); break;
    case 1: Quaternion_Lerp(quaternion, blend, (const float *)ka, (const float *)kb); break;
    case 0: quaternion[0] = kb->_quaternion[0]; quaternion[1] = kb->_quaternion[1]; quaternion[2] = kb->_quaternion[2]; quaternion[3] = kb->_quaternion[3]; break;
    case 2: break;
    }
    return 1;
}

bool igEnbayaAnimationSource::evaluateRotationAndTranslation(float *quaternion, float *translation, long long time, int *cachedLastTimeFrame, int flags, int trackId)
{
    return evaluateRotationAndTranslation(quaternion, translation, time, trackId);
}

void igEnbayaAnimationSource::userPostLoad()
{
    _enbayaAnimationStream = FUN_002808f0(_enbayaAnimationStream);
}

unsigned long long igEnbayaAnimationSource::getDurationNs()
{
    return (unsigned long long)(1000000000 * (double)((EnbayaStreamSlots *)_enbayaAnimationStream)->duration());
}
}
}

