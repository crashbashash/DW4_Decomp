void Gap__Sg__igTransformSource__vfunc_33(void) {

}

void FUN_001dd0e0(TransformSampleView *o, int index, float (*m)[4]) {
    float rot[4][4];
    float inv[3];
    float *t;
    float *s;
    int i;
    t = o->_xlateList->_data[index];
    t[0] = m[3][0];
    t[1] = m[3][1];
    t[2] = m[3][2];
    s = o->_scaleList->_data[index];
    for (i = 0; i < 3; i++) {
        float *r = m[i];
        s[i] = sqrtf(r[0] * r[0] + r[1] * r[1] + r[2] * r[2]);
    }
    Matrix44_Copy(rot, m);
    if (FUN_00192290(m) < 0.0f) {
        s[0] = -s[0];
        s[1] = -s[1];
        s[2] = -s[2];
    }
    {
        float z;
        float y;
        float x;
        z = 1.0f / s[2];
        x = 1.0f / s[0];
        y = 1.0f / s[1];
        inv[0] = x;
        inv[2] = z;
        inv[1] = y;
    }
    FUN_00190cb0(rot, inv);
    Matrix44_GetQuaternion(o->_quatList->_data[index], rot);
}

void FUN_001dd250(A_1dd250 *arg0, int arg1, char *arg2) {
    V3_1dd250 sp50;
    float f22, f21, f20;
    int idx;
    V3_1dd250 *v;
    FUN_00192810(arg0->b12->data + arg1 * 16, arg2);
    idx = arg1 * 12;
    v = (V3_1dd250 *)(arg0->b8->data + idx);
    f22 = v->x;
    f21 = v->y;
    f20 = v->z;
    if (arg0->f44 == 0.0f && arg0->f48 == 0.0f && arg0->f52 == 0.0f) {
    } else {
        Vec3f_TransformDirection(&sp50, &arg0->f44, arg2);
        f22 = f22 - sp50.x;
        f21 = f21 - sp50.y;
        f20 = f20 - sp50.z;
        f22 = f22 + arg0->f44;
        f21 = f21 + arg0->f48;
        f20 = f20 + arg0->f52;
    }
    *(float *)(arg2 + 48) = f22;
    *(float *)(arg2 + 52) = f21;
    *(float *)(arg2 + 56) = f20;
    FUN_00190cb0(arg2, arg0->b16->data + idx);
}

int FUN_001dd370(void *arg0) {
    int var_v0;

    var_v0 = 1;
    if (*(float *)((char *)(arg0) + 44) == g_vec3Zero[0]) {
        var_v0 = 0;
    }
    if (var_v0 == 0) {
        var_v0 = 1;
        if (*(float *)((char *)(arg0) + 48) == DAT_004e105c[0]) {
            var_v0 = 0;
        }
    }
    if (var_v0 == 0) {
        var_v0 = 1;
        if (*(float *)((char *)(arg0) + 52) == DAT_004e1060[0]) {
            var_v0 = 0;
        }
    }
    return var_v0 ^ 1;
}

void FUN_001dd3e0(void *arg0, int arg1) {
    int sp50[16];
    int n;
    int i;
    n = ((V_1dd3e0 *)arg0)->vCount();
    for (i = 0; i < n; i++) {
        igMatrix44f_SetIdentity(sp50);
        ((V_1dd3e0 *)arg0)->vGet(i, sp50);
        FUN_001904f0(sp50, sp50, arg1);
        ((V_1dd3e0 *)arg0)->vSet(i, sp50);
        ((F_1dd3e0 *)arg0)->a = g_vec3Zero[0];
        ((F_1dd3e0 *)arg0)->b = DAT_004e105c[0];
        ((F_1dd3e0 *)arg0)->c = DAT_004e1060[0];
    }
}

int UnsignedDivMod64_Cached(long long arg0, long long arg1, long long *arg2) {
    long long r, v;
    if (DAT_00562a18[0] == arg0 && arg1 == DAT_00562a20[0]) {
        *arg2 = DAT_00562a30[0];
        return DAT_00562a28[0];
    } else {
        DAT_00562a18[0] = arg0;
        DAT_00562a20[0] = arg1;
        r = __udivdi3(arg0, arg1);
        v = arg0 - __muldi3(r, arg1);
        DAT_00562a30[0] = v;
        *arg2 = v;
        DAT_00562a28[0] = (int)r;
    }
    return DAT_00562a28[0];
}

