void igMatrix44f_SetIdentity(float matrix[16]) {
    matrix[0] = 1.0f;
    matrix[1] = 0.0f;
    matrix[2] = 0.0f;
    matrix[3] = 0.0f;
    matrix[4] = 0.0f;
    matrix[5] = 1.0f;
    matrix[6] = 0.0f;
    matrix[7] = 0.0f;
    matrix[8] = 0.0f;
    matrix[9] = 0.0f;
    matrix[10] = 1.0f;
    matrix[11] = 0.0f;
    matrix[12] = 0.0f;
    matrix[13] = 0.0f;
    matrix[14] = 0.0f;
    matrix[15] = 1.0f;
}

void FUN_001903d0(float *a) {
    float m[16];
    m[0] = a[0];
    m[1] = a[4];
    m[2] = a[8];
    m[3] = a[12];
    m[4] = a[1];
    m[5] = a[5];
    m[6] = a[9];
    m[7] = a[13];
    m[8] = a[2];
    m[9] = a[6];
    m[10] = a[10];
    m[11] = a[14];
    m[12] = a[3];
    m[13] = a[7];
    m[14] = a[11];
    m[15] = a[15];
    Matrix44_Copy(a, m);
}

void Matrix44_FromTranslation(float *matrix, const float *vector) {
    matrix[0]=1.0f; matrix[1]=0; matrix[2]=0; matrix[3]=0;
    matrix[4]=0; matrix[5]=1.0f; matrix[6]=0; matrix[7]=0;
    matrix[8]=0; matrix[9]=0; matrix[10]=1.0f; matrix[11]=0;
    matrix[12]=vector[0]; matrix[13]=vector[1]; matrix[14]=vector[2]; matrix[15]=1.0f;
}

void Matrix44_SetTranslation(float *matrix, const float *vector) {
    matrix[12] = vector[0];
    matrix[13] = vector[1];
    matrix[14] = vector[2];
}

void Matrix44_GetTranslation(const float *matrix, float *vector) {
    vector[0] = matrix[12];
    vector[1] = matrix[13];
    vector[2] = matrix[14];
}

void FUN_00190b30(float *m, const ScaleVec &v) {
    m[0] += m[3] * v[0];
    m[1] += m[3] * v[1];
    m[2] += m[3] * v[2];
    m[4] += m[7] * v[0];
    m[5] += m[7] * v[1];
    m[6] += m[7] * v[2];
    m[8] += m[11] * v[0];
    m[9] += m[11] * v[1];
    m[10] += m[11] * v[2];
    m[12] += m[15] * v[0];
    m[13] += m[15] * v[1];
    m[14] += m[15] * v[2];
}

void FUN_00190c60(void *arg0, void *arg1) {
    igMatrix44f_SetIdentity((float *)arg0);
    *(float *)((char *)(arg0) + 0) = (float) *(float *)((char *)(arg1) + 0);
    *(float *)((char *)(arg0) + 20) = (float) *(float *)((char *)(arg1) + 4);
    *(float *)((char *)(arg0) + 40) = (float) *(float *)((char *)(arg1) + 8);
}

void FUN_00190cb0(float *matrix, const float *scale) {
    matrix[0] *= scale[0];
    matrix[1] *= scale[0];
    matrix[2] *= scale[0];
    matrix[3] *= scale[0];
    matrix[4] *= scale[1];
    matrix[5] *= scale[1];
    matrix[6] *= scale[1];
    matrix[7] *= scale[1];
    matrix[8] *= scale[2];
    matrix[9] *= scale[2];
    matrix[10] *= scale[2];
    matrix[11] *= scale[2];
}

void FUN_00190d80(float *m, const ScaleVec &v) {
    m[0] *= v[0];
    m[1] *= v[1];
    m[2] *= v[2];
    m[4] *= v[0];
    m[5] *= v[1];
    m[6] *= v[2];
    m[8] *= v[0];
    m[9] *= v[1];
    m[10] *= v[2];
    m[12] *= v[0];
    m[13] *= v[1];
    m[14] *= v[2];
}

void FUN_00190e50(void *arg0, float *arg1, float fparg0) {
    FUN_00190f50((float *)arg0, arg1, fparg0);
    *(float *)((char *)(arg0) + 48) = (float) DAT_004e11c0[0];
    *(float *)((char *)(arg0) + 52) = (float) DAT_004e11c4[0];
    *(float *)((char *)(arg0) + 56) = (float) DAT_004e11c8[0];
    *(float *)((char *)(arg0) + 60) = (float) DAT_004e11cc[0];
    *(float *)((char *)(arg0) + 12) = (float) g_vec3Zero[0];
    *(float *)((char *)(arg0) + 28) = (float) DAT_004e105c[0];
    *(float *)((char *)(arg0) + 44) = (float) DAT_004e1060[0];
}

void FUN_00190ed0(void *arg0, float x, float y, float z) {
    FUN_001910c0((float *)arg0, x, y, z);
    *(float *)((char *)(arg0) + 48) = (float) DAT_004e11c0[0];
    *(float *)((char *)(arg0) + 52) = (float) DAT_004e11c4[0];
    *(float *)((char *)(arg0) + 56) = (float) DAT_004e11c8[0];
    *(float *)((char *)(arg0) + 60) = (float) DAT_004e11cc[0];
    *(float *)((char *)(arg0) + 12) = (float) g_vec3Zero[0];
    *(float *)((char *)(arg0) + 28) = (float) DAT_004e105c[0];
    *(float *)((char *)(arg0) + 44) = (float) DAT_004e1060[0];
}

/* Axis-angle rotation matrix (Rodrigues); the sign bit is cleared through a byte bit-field union,
 * and partial products are split so the adds keep their operand order. */
void FUN_00190f50(float *arg0, float *arg1, float fparg0) {
    U5 u;
    float p1;
    float p6;
    float p8;
    float s;
    float c;
    float f7;
    float f6;
    float f5;
    float f3;
    float f2;
    float f2b;
    float f4;
    float f2c;
    float one;
    u.f = fparg0;
    u.b.sign = 0;
    if (u.f < 4.99999999e-07f) {
        arg0[10] = 1.0f;
        arg0[5] = 1.0f;
        arg0[0] = 1.0f;
        arg0[9] = 0.0f;
        arg0[8] = 0.0f;
        arg0[6] = 0.0f;
        arg0[4] = 0.0f;
        arg0[2] = 0.0f;
        arg0[1] = 0.0f;
        return;
    }
    s = sinf(fparg0);
    c = cosf(fparg0);
    f4 = arg1[0];
    one = 1.0f;
    f5 = s * arg1[1];
    f3 = s * arg1[2];
    f7 = one - c;
    f2 = f7 * f4;
    arg0[0] = c + f2 * f4;
    f6 = s * f4;
    p1 = f2 * arg1[1];
    arg0[1] = p1 + f3;
    arg0[2] = f2 * arg1[2] - f5;
    f2b = f7 * arg1[1];
    arg0[4] = f2b * arg1[0] - f3;
    arg0[5] = c + f2b * arg1[1];
    p6 = f2b * arg1[2];
    arg0[6] = p6 + f6;
    f2c = f7 * arg1[2];
    p8 = f2c * arg1[0];
    arg0[8] = p8 + f5;
    arg0[9] = f2c * arg1[1] - f6;
    arg0[10] = c + f2c * arg1[2];
}

void FUN_001910c0(float *m, float x, float y, float z) {
    float sx;
    float sxy;
    float sy;
    float sz;
    float cx;
    float cz;
    float t3;
    float t2;
    float cy;
    sx = 0.0f;
    if (x != 0.0f) {
        sx = sinf(x);
        cx = cosf(x);
    } else {
        cx = 1.0f;
    }
    sy = 0.0f;
    if (y != 0.0f) {
        sy = sinf(y);
        cy = cosf(y);
        sxy = sx * sy;
    } else {
        cy = 1.0f;
        sxy = sy;
    }
    sz = 0.0f;
    if (z != 0.0f) {
        sz = sinf(z);
        cz = cosf(z);
        t3 = cx * sz;
    } else {
        cz = 1.0f;
        t3 = sz;
    }
    m[0] = cy * cz;
    m[1] = cy * sz;
    m[2] = -sy;
    m[4] = sxy * cz - t3;
    m[5] = sxy * sz + cx * cz;
    m[6] = sx * cy;
    t2 = cx * cz;
    m[8] = t2 * sy + sx * sz;
    m[9] = t3 * sy - sx * cz;
    m[10] = cx * cy;
}

void FUN_00191670(int arg0, float *arg1, float fparg0) {
    int buf[16];

    FUN_00190e50(buf, arg1, fparg0);
    FUN_001906d0(arg0, buf);
}

void FUN_001916b0(int arg0, float *arg1, float fparg0) {
    int sp20[14];
    FUN_00190e50(sp20, arg1, fparg0);
    FUN_001904f0(arg0, arg0, sp20);
}

void FUN_001916f0(void *arg0, float *arg1) {
    Matrix44_SetQuaternion((float *)arg0, arg1);
    *(float *)((char *)(arg0) + 48) = (float) DAT_004e11c0[0];
    *(float *)((char *)(arg0) + 52) = (float) DAT_004e11c4[0];
    *(float *)((char *)(arg0) + 56) = (float) DAT_004e11c8[0];
    *(float *)((char *)(arg0) + 60) = (float) DAT_004e11cc[0];
    *(float *)((char *)(arg0) + 12) = (float) g_vec3Zero[0];
    *(float *)((char *)(arg0) + 28) = (float) DAT_004e105c[0];
    *(float *)((char *)(arg0) + 44) = (float) DAT_004e1060[0];
}

void Matrix44_SetQuaternion(float *m, float *q) {
    float x = q[0], y = q[1], z = q[2], w = q[3];
    float n = 1.0f / sqrtf(z * z + (x * x + y * y) + w * w);
    y = y * n;
    z = z * n;
    w = w * n;
    x = x * n;
    m[0] = 1.0f - 2.0f * (y * y + z * z);
    m[1] = 2.0f * (x * y - z * w);
    m[2] = 2.0f * (z * x + y * w);
    m[4] = 2.0f * (x * y + z * w);
    m[5] = 1.0f - 2.0f * (z * z + x * x);
    m[6] = 2.0f * (y * z - x * w);
    m[8] = 2.0f * (z * x - y * w);
    m[9] = 2.0f * (y * z + x * w);
    m[10] = 1.0f - 2.0f * (y * y + x * x);
}

void FUN_00191860(float *m, float l, float r, float b, float t, float n, float f) {
 float x, y, z;
x = 1.0f / (r - l);
m[0] = 2.0f * x;
m[4] = 0;
m[8] = 0;
m[12] = x * -(r + l);
y = 1.0f / (t - b);
m[1] = 0;
m[5] = 2.0f * y;
m[9] = 0;
m[13] = y * -(t + b);
z = 1.0f / (f - n);
m[2] = 0;
m[6] = 0;
m[10] = -2.0f * z;
m[14] = z * -(f + n);
m[3] = 0;
m[7] = 0;
m[11] = 0;
m[15] = 1.0f;
}

void FUN_00191910(float *m, float l, float r, float b, float t, float n, float f) {
    float rw, n2, rh, rd;
    rw = 1.0f / (r - l);
    n2 = 2.0f * n;
    m[0] = n2 * rw;
    m[4] = 0;
    rh = 1.0f / (t - b);
    m[8] = rw * (r + l);
    m[12] = 0;
    m[1] = 0;
    m[5] = n2 * rh;
    m[9] = rh * (t + b);
    m[13] = 0;
    m[2] = 0;
    m[6] = 0;
    rd = 1.0f / (f - n);
    m[10] = rd * -(f + n);
    m[14] = rd * (-2.0f * f * n);
    m[3] = 0;
    m[7] = 0;
    m[11] = -1.0f;
    m[15] = 0;
}

void FUN_001919d0(int arg0, float a, float b, float c, float d, float e) {
    float t23;
    float t14;

    if (a < 0.0f) {
        a = 2.0f * atanf((c * (d * tanf(0.5f * b))) / d);
    } else {
        b = 2.0f * atanf(((d * tanf(0.5f * a)) / c) / d);
    }
    t23 = d * -tanf(0.5f * a);
    t14 = d * -tanf(0.5f * b);
    FUN_00191910((float *)arg0, t23, -t23, t14, -t14, d, e);
}

void FUN_00191e30(int *r, float *o, float *m) {
    o[0] = m[0]; o[1] = m[4]; o[2] = m[8];
    o[4] = m[1]; o[5] = m[5]; o[6] = m[9];
    o[8] = m[2]; o[9] = m[6]; o[10] = m[10];
    o[11] = 0; o[7] = 0; o[3] = 0;
    o[15] = 1.0f;
    o[12] = -(m[12] * o[0] + m[13] * o[4] + m[14] * o[8]);
    o[13] = -(m[12] * o[1] + m[13] * o[5] + m[14] * o[9]);
    o[14] = -(m[12] * o[2] + m[13] * o[6] + m[14] * o[10]);
    *r = g_statusSucceeded[0];
}

/* The sign bit is cleared through a byte bit-field union. */
void FUN_00191f30(int *arg0, float *arg1, int arg2) {
    float tmp[16];
    U6 u;
    float len;
    int i, j;
    FUN_00192030((int)arg1, arg2, tmp);
    len = FUN_00192290((float *)arg2);
    u.f = len;
    u.b.sign = 0;
    if (u.f < 1.1754944e-38f) {
        *arg0 = g_allocatorFailureStatus[0];
    } else {
        float inv = 1.0f / len;
        i = 0;
        do {
            int off = i * 0x10;
            j = 0;
            do {
                int jo = j * 4;
                float *sv = (float *)((char *)tmp + off + jo);
                j++;
                *(float *)((char *)arg1 + off + jo) = inv * *sv;
            } while (j < 4);
            i++;
        } while (i < 4);
        *arg0 = g_statusSucceeded[0];
    }
}

float FUN_00192290(float *m) {
    float B, m10, E2, m02, m20, A, m30, PB, m11, m21, C1, D1, m31, B1, m12, A1, m13, m03, c12, m01, E1, PE, C, c03, m22, D, c13, m32, PD, c02, c01, m00, m23, m33, c23;
    m10 = m[4];
    m02 = m[2];
    m31 = m[13];
    m21 = m[9];
    m20 = m[8];
    m23 = m[11];
    m00 = m[0];
    m01 = m[1];
    m33 = m[15];
    m12 = m[6];
    m22 = m[10];
    m03 = m[3];
    m30 = m[12];
    m13 = m[7];
    m32 = m[14];
    m11 = m[5];
    c03 = m20 * m33 - m30 * m23;
    c23 = m22 * m33 - m32 * m23;
    c02 = m20 * m32 - m30 * m22;
    c13 = m21 * m33 - m31 * m23;
    PB = m13 * c02;
    A1 = m11 * c23 - m12 * c13;
    c12 = m21 * m32 - m31 * m22;
    c01 = m20 * m31 - m30 * m21;
    D1 = m10 * c12 - m11 * c02;
    C1 = m10 * c13 - m11 * c03;
    C = C1 + m13 * c01;
    A = A1 + m13 * c12;
    B1 = m10 * c23 - m12 * c03;
    PE = m02 * C;
    PD = m12 * c01;
    B = PB + B1;
    D = PD + D1;
    E1 = m00 * A - m01 * B;
    E2 = PE + E1;
    return E2 - m03 * D;
}

void FUN_00192510(S6 *a, float *arg1, float *arg2, float *arg3, float *arg4, float *arg5, float *arg6) {
    float t2;
    float t6;
    float t5;
    float tf2;
    float t3;
    float t1;
    float t0;
    t6 = a->f56 / 2.0f;
    tf2 = a->f40;
    t5 = 1.0f + tf2;
    t2 = 1.0f - tf2;
    if (t2 == 0.0f || t5 == 0.0f || a->f0 == 0.0f) return;
    *arg5 = -t6 * (1.0f + (t5 / t2));
    *arg6 = t6 * (1.0f + (t2 / t5));
    t3 = *arg5 / a->f0;
    *arg1 = -(t3 * (1.0f - a->f32));
    t1 = 2.0f * t3;
    *arg2 = t1 + *arg1;
    t0 = -(t3 * (1.0f - a->f36));
    *arg3 = t0;
    *arg4 = t1 + t0;
}

void Matrix44_GetQuaternion(float *q, float *m) {
    float tr = m[10] + (m[0] + m[5]);
    if (!(tr < 0.0f)) {
        float s, r; s = sqrtf(1.0f + tr);
        q[3] = 0.5f * s;
        r = 0.5f / s;
        q[0] = r * (m[9] - m[6]);
        q[1] = r * (m[2] - m[8]);
        q[2] = r * (m[4] - m[1]);
        return;
    }
    {
        int i;
        i = 0;
        if (!(m[5] <= m[0])) i = 1;
        if (!(m[10] <= *(float*)((char*)m + i*16 + i*4))) i = 2;
        switch (i) {
        case 0: {
            float s, r; s = sqrtf(m[15] + (m[0] - (m[5] + m[10])));
            q[0] = 0.5f * s;
            r = 0.5f / s;
            q[1] = r * (m[1] + m[4]);
            q[2] = r * (m[8] + m[2]);
            q[3] = r * (m[9] - m[6]);
            break; }
        case 1: {
            float s, r; s = sqrtf(m[15] + (m[5] - (m[10] + m[0])));
            q[1] = 0.5f * s;
            r = 0.5f / s;
            q[2] = r * (m[6] + m[9]);
            q[0] = r * (m[1] + m[4]);
            q[3] = r * (m[2] - m[8]);
            break; }
        case 2: {
            float s, r; s = sqrtf(m[15] + (m[10] - (m[0] + m[5])));
            q[2] = 0.5f * s;
            r = 0.5f / s;
            q[0] = r * (m[8] + m[2]);
            q[1] = r * (m[6] + m[9]);
            q[3] = r * (m[4] - m[1]);
            break; }
        }
    }
}

void FUN_00192810(void *arg0, void *arg1) {
    float temp_f12;
    float temp_f6;
    float temp_f5;
    float temp_f11;
    float temp_f10;
    float temp_f9;
    float temp_f4;
    float temp_f8;
    float temp_f7;
    float temp_f1_2;
    float temp_f0;
    float temp_f6_2;
    float temp_f4_2;
    float temp_f3;
    float temp_f1;
    float temp_f5_2;

    temp_f4 = *(float *)((char *)(arg0) + 0);
    temp_f3 = *(float *)((char *)(arg0) + 4);
    temp_f1 = *(float *)((char *)(arg0) + 8);
    temp_f5 = *(float *)((char *)(arg0) + 12);
    temp_f6 = 2.0f * temp_f4;
    temp_f12 = 2.0f * temp_f3;
    temp_f0 = 2.0f * temp_f1;
    temp_f11 = temp_f6 * temp_f5;
    temp_f8 = temp_f6 * temp_f4;
    temp_f10 = temp_f12 * temp_f5;
    temp_f9 = temp_f0 * temp_f5;
    temp_f7 = temp_f12 * temp_f4;
    temp_f6_2 = temp_f0 * temp_f4;
    temp_f1_2 = temp_f0 * temp_f1;
    temp_f4_2 = temp_f12 * temp_f3;
    temp_f5_2 = temp_f0 * temp_f3;
    *(float *)((char *)(arg1) + 0) = (float) (1.0f - (temp_f4_2 + temp_f1_2));
    *(float *)((char *)(arg1) + 4) = (float) (temp_f7 - temp_f9);
    *(float *)((char *)(arg1) + 8) = (float) (temp_f6_2 + temp_f10);
    *(float *)((char *)(arg1) + 16) = (float) (temp_f7 + temp_f9);
    *(float *)((char *)(arg1) + 20) = (float) (1.0f - (temp_f8 + temp_f1_2));
    *(float *)((char *)(arg1) + 24) = (float) (temp_f5_2 - temp_f11);
    *(float *)((char *)(arg1) + 32) = (float) (temp_f6_2 - temp_f10);
    *(float *)((char *)(arg1) + 36) = (float) (temp_f5_2 + temp_f11);
    *(float *)((char *)(arg1) + 40) = (float) (1.0f - (temp_f8 + temp_f4_2));
    *(int *)((char *)(arg1) + 12) = 0;
    *(int *)((char *)(arg1) + 28) = 0;
    *(int *)((char *)(arg1) + 44) = 0;
    *(int *)((char *)(arg1) + 48) = 0;
    *(int *)((char *)(arg1) + 52) = 0;
    *(int *)((char *)(arg1) + 56) = 0;
    *(int *)((char *)(arg1) + 60) = 0x3F800000;
}

void FUN_00192990(int arg0, float *arg1, float *arg2, float *arg3) {
    float m[16];
    float t;
    float x;
    float r;

    igMatrix44f_SetIdentity(m);
    FUN_001916f0(m, (float *)arg0);
    x = -m[2];
    t = (x > -1.0f) ? x : -1.0f;
    if (t < 1.0f) {
        x = (x > -1.0f) ? x : -1.0f;
    } else {
        x = 1.0f;
    }
    r = asinf(x);
    *arg2 = r;
    if (cosf(r) != 0.0f) {
        *arg1 = atan2f(m[6], m[10]);
        *arg3 = atan2f(m[1], m[0]);
        return;
    }
    *arg2 = atan2f(m[4], m[5]);
    *arg3 = 0.0f;
}

void FUN_00192dd0(float *arg0, float *arg1, float *arg2) {
    float b0; float a0; float b1; float a2; float b2; float a1;
    a0 = arg1[0];
    b0 = arg2[0];
    b2 = arg2[2];
    a2 = arg1[2];
    b1 = arg2[1];
    a1 = arg1[1];
    arg0[0] = a1 * b2 - a2 * b1;
    arg0[1] = a2 * b0 - a0 * b2;
    arg0[2] = a0 * b1 - a1 * b0;
}

void FUN_00192e10(float *arg0, float *arg1) {
    float b0; float a0; float b1; float a2; float b2; float a1;
    b2 = arg1[2]; a1 = arg0[1]; a0 = arg0[0]; b1 = arg1[1]; a2 = arg0[2]; b0 = arg1[0];
    arg0[0] = a1 * b2 - a2 * b1;
    arg0[1] = a2 * b0 - a0 * b2;
    arg0[2] = a0 * b1 - a1 * b0;
}

