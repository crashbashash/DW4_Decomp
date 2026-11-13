void FUN_001c07d0(void) {
    thunk_FUN_00280a00(0);
}

void FUN_001c07e0(void) {

}

void Gap__Sg__igEnbayaAnimationSource__vfunc_13(void *arg0) {
    *(char *)((char *)(arg0) + 8) = 1;
    *(char *)((char *)(arg0) + 9) = 3;
    *(char *)((char *)(arg0) + 10) = 1;
}

int Gap__Sg__igEnbayaAnimationSource__vfunc_23(void **arg0, int arg1, int arg2, int arg3) {
    int sp40[4];
    int sp30[4];
    int temp_s0;

    temp_s0 = ((DW4VC_108_4 *)(arg0))->vX((int)sp30, (int)sp40, (int)(arg2), (int)(arg3)) & 0xFF;
    FUN_00192810(sp30, arg1);
    Matrix44_SetTranslation(arg1, sp40);
    return temp_s0;
}

int Gap__Sg__igEnbayaAnimationSource__vfunc_24(EnbayaSourceSlots24 *o, int a, int b, int c, int d, int e) {
    return o->f(a, b, e);
}

int Gap__Sg__igEnbayaAnimationSource__vfunc_25(EnbayaSourceView *o, float *out, long long time, int track) {
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
        case 4: duration += g_enbayaPlayOnceEndOffset[0]; case 1: if (t > duration) { r = duration; } else if (t < 0.0f) { r = 0.0f; } else { FUN_001c0ae0(&r, t, duration); } break;
        case 3: case 0: FUN_001c0ae0(&r, t, duration); break;
        case 2: if (FUN_001c0ae0(&r, t, duration) & 1) { r = duration - r; } break;
        default: r = 0.0f; break;
        }
        t = r;
        o->_lastUpdateTimef = t;
        o->_lastUpdateTime = time;
    }
    decoder = ((EnbayaDecoderView * *)DAT_00562720)[0];
    a = 0;
    b = 0;
    FUN_0027fa60(decoder, t, track, &a, &b);
    ka = a;
    kb = b;
    blend = (t - ka->_translation[3]) / decoder->_interval;
    switch (o->_interpolationMethod[1]) {
    case 3: FUN_00192ab0(out, blend, (void *)ka, (void *)kb); break;
    case 1: Quaternion_Lerp(out, blend, (void *)ka, (void *)kb); break;
    case 0: out[0] = kb->_quaternion[0]; out[1] = kb->_quaternion[1]; out[2] = kb->_quaternion[2]; out[3] = kb->_quaternion[3]; break;
    case 2: break;
    }
    return 1;
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

int Gap__Sg__igEnbayaAnimationSource__vfunc_26(EnbayaSourceSlots26 *o, int a, int b, int c, int d, int e) {
    return o->f(a, b, e);
}

int Gap__Sg__igEnbayaAnimationSource__vfunc_27(EnbayaSourceView *o, float *out, float *pos, long long time, int track) {
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
        case 4: duration += g_enbayaPlayOnceEndOffset[0]; case 1: if (t > duration) { r = duration; } else if (t < 0.0f) { r = 0.0f; } else { FUN_001c0ae0(&r, t, duration); } break;
        case 3: case 0: FUN_001c0ae0(&r, t, duration); break;
        case 2: if (FUN_001c0ae0(&r, t, duration) & 1) { r = duration - r; } break;
        default: r = 0.0f; break;
        }
        t = r;
        o->_lastUpdateTimef = t;
        o->_lastUpdateTime = time;
    }
    decoder = ((EnbayaDecoderView * *)DAT_00562720)[0];
    a = 0;
    b = 0;
    FUN_0027fa60(decoder, t, track, &a, &b);
    ka = a;
    kb = b;
    blend = (t - ka->_translation[3]) / decoder->_interval;
    ta = ka->_translation;
    tb = kb->_translation;
    switch (o->_interpolationMethod[0]) {
    case 1: Vec3_Lerp(pos, blend, (void *)ta, (void *)tb); break;
    case 0: pos[0] = tb[0]; pos[1] = tb[1]; pos[2] = tb[2]; pos[3] = tb[3]; break;
    case 3: case 2: break;
    }
    switch (o->_interpolationMethod[1]) {
    case 3: FUN_00192ab0(out, blend, (void *)ka, (void *)kb); break;
    case 1: Quaternion_Lerp(out, blend, (void *)ka, (void *)kb); break;
    case 0: out[0] = kb->_quaternion[0]; out[1] = kb->_quaternion[1]; out[2] = kb->_quaternion[2]; out[3] = kb->_quaternion[3]; break;
    case 2: break;
    }
    return 1;
}

int Gap__Sg__igEnbayaAnimationSource__vfunc_28(EnbayaSourceSlots28 *o, int a, int b, int c, int d, int e, int g) {
    return o->f(a, b, c, g);
}

void Gap__Sg__igEnbayaAnimationSource__vfunc_17(Obj_1c0e70 *arg0) {
    arg0->f32 = FUN_002808f0(arg0->f32);
}

unsigned long long FUN_001c0ea0(EnbayaSourceView *o) {
    return (unsigned long long)(1000000000 * (double)o->_enbayaAnimationStream->duration());
}

