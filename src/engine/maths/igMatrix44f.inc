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
    igMatrix44f_Copy(a, m);
}

/* product = a * b, all three 16-byte aligned. */
void FUN_00190470(float *product, const float *a, const float *b) {
    asm {
            lqc2 vf1, 0(a)
            lqc2 vf2, 16(a)
            lqc2 vf3, 32(a)
            lqc2 vf4, 48(a)
            lqc2 vf5, 0(b)
            lqc2 vf6, 16(b)
            lqc2 vf7, 32(b)
            lqc2 vf8, 48(b)
            vmulax.xyzw ACC, vf5, vf1x
            vmadday.xyzw ACC, vf6, vf1y
            vmaddaz.xyzw ACC, vf7, vf1z
            vmaddw.xyzw vf9, vf8, vf1w
            vmulax.xyzw ACC, vf5, vf2x
            vmadday.xyzw ACC, vf6, vf2y
            vmaddaz.xyzw ACC, vf7, vf2z
            vmaddw.xyzw vf10, vf8, vf2w
            vmulax.xyzw ACC, vf5, vf3x
            vmadday.xyzw ACC, vf6, vf3y
            vmaddaz.xyzw ACC, vf7, vf3z
            vmaddw.xyzw vf11, vf8, vf3w
            vmulax.xyzw ACC, vf5, vf4x
            vmadday.xyzw ACC, vf6, vf4y
            vmaddaz.xyzw ACC, vf7, vf4z
            vmaddw.xyzw vf12, vf8, vf4w
            sqc2 vf9, 0(product)
            sqc2 vf10, 16(product)
            sqc2 vf11, 32(product)
            sqc2 vf12, 48(product)
    }
}

void igMatrix44f_Copy(float *destination, const float *source) {
    if ((((unsigned int)destination | (unsigned int)source) & 0xF) == 0) {
        asm {
            lq a2, 0(source)
            lq a3, 16(source)
            lq t0, 32(source)
            lq t1, 48(source)
            sq a2, 0(destination)
            sq a3, 16(destination)
            sq t0, 32(destination)
            sq t1, 48(destination)
        }
    } else {
        destination[0] = source[0];
        destination[1] = source[1];
        destination[2] = source[2];
        destination[3] = source[3];
        destination[4] = source[4];
        destination[5] = source[5];
        destination[6] = source[6];
        destination[7] = source[7];
        destination[8] = source[8];
        destination[9] = source[9];
        destination[10] = source[10];
        destination[11] = source[11];
        destination[12] = source[12];
        destination[13] = source[13];
        destination[14] = source[14];
        destination[15] = source[15];
    }
}

void igMatrix44f_FromTranslation(float *matrix, const igVec3f &translation) {
    matrix[0]=1.0f; matrix[1]=0; matrix[2]=0; matrix[3]=0;
    matrix[4]=0; matrix[5]=1.0f; matrix[6]=0; matrix[7]=0;
    matrix[8]=0; matrix[9]=0; matrix[10]=1.0f; matrix[11]=0;
    matrix[12]=translation[0]; matrix[13]=translation[1]; matrix[14]=translation[2]; matrix[15]=1.0f;
}

void igMatrix44f_SetTranslation(float *matrix, const float *vector) {
    matrix[12] = vector[0];
    matrix[13] = vector[1];
    matrix[14] = vector[2];
}

void igMatrix44f_GetTranslation(const float *matrix, float *vector) {
    vector[0] = matrix[12];
    vector[1] = matrix[13];
    vector[2] = matrix[14];
}

void igMatrix44f_TranslateLocal(float *m, const igVec3f &v) {
    m[12] += m[0] * v[0] + m[4] * v[1] + m[8] * v[2];
    m[13] += m[1] * v[0] + m[5] * v[1] + m[9] * v[2];
    m[14] += m[2] * v[0] + m[6] * v[1] + m[10] * v[2];
    m[15] += m[3] * v[0] + m[7] * v[1] + m[11] * v[2];
}

void igMatrix44f_TranslateWorld(float *m, const igVec3f &v) {
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

void FUN_00190c60(float *matrix, const float *scale) {
    igMatrix44f_SetIdentity(matrix);
    matrix[0] = scale[0];
    matrix[5] = scale[1];
    matrix[10] = scale[2];
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

void FUN_00190e50(void *arg0, const float *arg1, float fparg0) {
    FUN_00190f50((float *)arg0, arg1, fparg0);
    *(float *)((char *)(arg0) + 48) = (float) g_vec4WAxis[0];
    *(float *)((char *)(arg0) + 52) = (float) g_vec4WAxis[1];
    *(float *)((char *)(arg0) + 56) = (float) g_vec4WAxis[2];
    *(float *)((char *)(arg0) + 60) = (float) g_vec4WAxis[3];
    *(float *)((char *)(arg0) + 12) = (float) g_vec3Zero[0];
    *(float *)((char *)(arg0) + 28) = (float) g_vec3Zero[1];
    *(float *)((char *)(arg0) + 44) = (float) g_vec3Zero[2];
}

void igMatrix44f_MakeEulerRotation(void *arg0, float x, float y, float z) {
    igMatrix44f_SetEulerRotation((float *)arg0, x, y, z);
    *(float *)((char *)(arg0) + 48) = (float) g_vec4WAxis[0];
    *(float *)((char *)(arg0) + 52) = (float) g_vec4WAxis[1];
    *(float *)((char *)(arg0) + 56) = (float) g_vec4WAxis[2];
    *(float *)((char *)(arg0) + 60) = (float) g_vec4WAxis[3];
    *(float *)((char *)(arg0) + 12) = (float) g_vec3Zero[0];
    *(float *)((char *)(arg0) + 28) = (float) g_vec3Zero[1];
    *(float *)((char *)(arg0) + 44) = (float) g_vec3Zero[2];
}

/* Axis-angle rotation matrix (Rodrigues); the sign bit is cleared through a byte bit-field union,
 * and partial products are split so the adds keep their operand order. */
void FUN_00190f50(float *arg0, const float *arg1, float fparg0) {
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

void igMatrix44f_SetEulerRotation(float *m, float x, float y, float z) {
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

/* dst += scale * src, the scaled term written first.
 * matching construct: operand order — `dst += scale * src` (igVec3f::addScaled) swaps the two temporaries' registers */
static inline void addScaledRow(igVec3f &dst, float scale, const igVec3f &src) {
    dst.vec[0] = scale * src.vec[0] + dst.vec[0];
    dst.vec[1] = scale * src.vec[1] + dst.vec[1];
    dst.vec[2] = scale * src.vec[2] + dst.vec[2];
}

/* Recovers the Euler angles of the matrix's rotation: the rows are scaled by 1/w, Gram-Schmidt
 * orthonormalised, and flipped when the basis is left-handed (igMatrix44f::getEulerAngles). The
 * pitch is the arcsine of the clamped third element; gimbal lock (cos pitch == 0) takes the roll
 * from the second row and leaves the yaw at zero. */
void igMatrix44f_GetEulerAngles(const float *m, float *x, float *y, float *z) {
    igVec3f cross;
    igVec3f r0;
    igVec3f r1;
    igVec3f r2;
    float s;
    float f;
    r0.set(&m[0]);
    r1.set(&m[4]);
    r2.set(&m[8]);
    if (m[15] != 1.0f) {
        s = 1.0f / m[15];
        r0.scale(s);
        r1.scale(s);
        r2.scale(s);
    }
    r0.normalize();
    f = -r0.dot(r1);
    addScaledRow(r1, f, r0);
    r1.normalize();
    f = -r0.dot(r2);
    addScaledRow(r2, f, r0);
    f = -r1.dot(r2);
    addScaledRow(r2, f, r1);
    r2.normalize();
    FUN_00192dd0(cross.vec, r1.vec, r2.vec);
    if (r0.dot(cross) < 0.0f) {
        r0[0] = -r0[0];
        r0[1] = -r0[1];
        r0[2] = -r0[2];
        r1[0] = -r1[0];
        r1[1] = -r1[1];
        r1[2] = -r1[2];
        r2[0] = -r2[0];
        r2[1] = -r2[1];
        r2[2] = -r2[2];
    }
    f = -r0[2];
    /* matching construct: the kit clamps with conditional macros, so the inner max is written twice (MIN(MAX(f, -1), 1)) */
    f = ((f > -1.0f) ? f : -1.0f) < 1.0f ? ((f > -1.0f) ? f : -1.0f) : 1.0f;
    *y = asinf(f);
    if (cosf(*y) != 0.0f) {
        *x = atan2f(r1[2], r2[2]);
        *z = atan2f(r0[1], r0[0]);
    } else {
        *x = atan2f(r1[0], r1[1]);
        *z = 0.0f;
    }
}

void igMatrix44f_PreRotateAxisAngle(float *matrix, const float *axis, float angle) {
    float rotation[16];

    FUN_00190e50(rotation, axis, angle);
    igMatrix44f_PreMultiply(matrix, rotation);
}

void igMatrix44f_PostRotateAxisAngle(float *matrix, const float *axis, float angle) {
    int rotation[14];
    FUN_00190e50(rotation, axis, angle);
    igMatrix44f_Multiply(matrix, matrix, (float *)rotation);
}

void FUN_001916f0(void *arg0, float *arg1) {
    igMatrix44f_SetQuaternion((float *)arg0, arg1);
    *(float *)((char *)(arg0) + 48) = (float) g_vec4WAxis[0];
    *(float *)((char *)(arg0) + 52) = (float) g_vec4WAxis[1];
    *(float *)((char *)(arg0) + 56) = (float) g_vec4WAxis[2];
    *(float *)((char *)(arg0) + 60) = (float) g_vec4WAxis[3];
    *(float *)((char *)(arg0) + 12) = (float) g_vec3Zero[0];
    *(float *)((char *)(arg0) + 28) = (float) g_vec3Zero[1];
    *(float *)((char *)(arg0) + 44) = (float) g_vec3Zero[2];
}

void igMatrix44f_SetQuaternion(float *m, float *q) {
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

void igMatrix44f_MakePerspective(float *matrix, float a, float b, float c, float d, float e) {
    float t23;
    float t14;

    if (a < 0.0f) {
        a = 2.0f * atanf((c * (d * tanf(0.5f * b))) / d);
    } else {
        b = 2.0f * atanf(((d * tanf(0.5f * a)) / c) / d);
    }
    t23 = d * -tanf(0.5f * a);
    t14 = d * -tanf(0.5f * b);
    FUN_00191910(matrix, t23, -t23, t14, -t14, d, e);
}

/* Scales the axis to unit length (igVec3f::normalize) unless it is shorter than the smallest normal float. */
static inline void normalizeAxis(igVec3f &axis) {
    float lengthSquared = axis.length2();
    float length;
    if (1.17549435e-38f < lengthSquared) {
        length = sqrtf(lengthSquared);
        axis.scale(1.0f / length);
    }
}

/* The view matrix looking from `eye` at `point`: the rows of the rotation are the camera's x, y and
 * z axes (z points from the point back to the eye), and the last row holds the eye rotated by them
 * (igMatrix44f::makeLookAt). An axis shorter than the smallest normal float is left as it is. */
void igMatrix44f_MakeLookAt(float *m, const float *eye, const float *point, const float *up) {
    igVec3f z;
    igVec3f upAxis;
    igVec3f x;
    igVec3f y;
    const igVec3f &e = *(const igVec3f *)eye;
    z.subtract(e, *(const igVec3f *)point);
    normalizeAxis(z);
    upAxis.set(up);
    normalizeAxis(upAxis);
    FUN_00192dd0(x.vec, upAxis.vec, z.vec);
    normalizeAxis(x);
    FUN_00192dd0(y.vec, z.vec, x.vec);
    m[0] = x[0];
    m[1] = y[0];
    m[2] = z[0];
    m[3] = 0.0f;
    m[4] = x[1];
    m[5] = y[1];
    m[6] = z[1];
    m[7] = 0.0f;
    m[8] = x[2];
    m[9] = y[2];
    m[10] = z[2];
    m[11] = 0.0f;
    m[12] = -(m[0] * e[0] + m[4] * e[1] + m[8] * e[2]);
    m[13] = -(m[1] * e[0] + m[5] * e[1] + m[9] * e[2]);
    m[14] = -(m[2] * e[0] + m[6] * e[1] + m[10] * e[2]);
    m[15] = 1.0f - (m[3] * e[0] + m[7] * e[1] + m[11] * e[2]);
}

igResult igMatrix44f_InvertOrthonormal(float *o, const float *m) {
    o[0] = m[0]; o[1] = m[4]; o[2] = m[8];
    o[4] = m[1]; o[5] = m[5]; o[6] = m[9];
    o[8] = m[2]; o[9] = m[6]; o[10] = m[10];
    o[11] = 0; o[7] = 0; o[3] = 0;
    o[15] = 1.0f;
    o[12] = -(m[12] * o[0] + m[13] * o[4] + m[14] * o[8]);
    o[13] = -(m[12] * o[1] + m[13] * o[5] + m[14] * o[9]);
    o[14] = -(m[12] * o[2] + m[13] * o[6] + m[14] * o[10]);
    return g_resultSuccess;
}

/* The sign bit is cleared through a byte bit-field union. */
igResult igMatrix44f_Invert(float *inverse, const float *matrix) {
    float tmp[16];
    U6 u;
    float len;
    int i, j;
    igMatrix44f_Adjugate(inverse, matrix, tmp);
    len = FUN_00192290(matrix);
    u.f = len;
    u.b.sign = 0;
    if (u.f < 1.1754944e-38f) {
        return g_resultFailure;
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
                *(float *)((char *)inverse + off + jo) = inv * *sv;
            } while (j < 4);
            i++;
        } while (i < 4);
        return g_resultSuccess;
    }
}

/* Adjugate (transposed cofactor matrix) of m, written to adjugate. */
void igMatrix44f_Adjugate(float *self, const float *m, float *adjugate) {
    float m00, m10, m20, m30;
    float m01, m11, m21, m31;
    float m02, m12, m22, m32;
    float m03, m13, m23, m33;

    m00 = m[0];
    m01 = m[1];
    m02 = m[2];
    m03 = m[3];
    m10 = m[4];
    m11 = m[5];
    m12 = m[6];
    m13 = m[7];
    m20 = m[8];
    m21 = m[9];
    m22 = m[10];
    m23 = m[11];
    m30 = m[12];
    m31 = m[13];
    m32 = m[14];
    m33 = m[15];
    adjugate[0] = m11 * (m22 * m33 - m32 * m23) - m12 * (m21 * m33 - m31 * m23) + m13 * (m21 * m32 - m31 * m22);
    adjugate[4] = -(m10 * (m22 * m33 - m32 * m23) - m12 * (m20 * m33 - m30 * m23) + m13 * (m20 * m32 - m30 * m22));
    adjugate[8] = m10 * (m21 * m33 - m31 * m23) - m11 * (m20 * m33 - m30 * m23) + m13 * (m20 * m31 - m30 * m21);
    adjugate[12] = -(m10 * (m21 * m32 - m31 * m22) - m11 * (m20 * m32 - m30 * m22) + m12 * (m20 * m31 - m30 * m21));
    adjugate[1] = -(m01 * (m22 * m33 - m32 * m23) - m02 * (m21 * m33 - m31 * m23) + m03 * (m21 * m32 - m31 * m22));
    adjugate[5] = m00 * (m22 * m33 - m32 * m23) - m02 * (m20 * m33 - m30 * m23) + m03 * (m20 * m32 - m30 * m22);
    adjugate[9] = -(m00 * (m21 * m33 - m31 * m23) - m01 * (m20 * m33 - m30 * m23) + m03 * (m20 * m31 - m30 * m21));
    adjugate[13] = m00 * (m21 * m32 - m31 * m22) - m01 * (m20 * m32 - m30 * m22) + m02 * (m20 * m31 - m30 * m21);
    adjugate[2] = m01 * (m12 * m33 - m32 * m13) - m02 * (m11 * m33 - m31 * m13) + m03 * (m11 * m32 - m31 * m12);
    adjugate[6] = -(m00 * (m12 * m33 - m32 * m13) - m02 * (m10 * m33 - m30 * m13) + m03 * (m10 * m32 - m30 * m12));
    adjugate[10] = m00 * (m11 * m33 - m31 * m13) - m01 * (m10 * m33 - m30 * m13) + m03 * (m10 * m31 - m30 * m11);
    adjugate[14] = -(m00 * (m11 * m32 - m31 * m12) - m01 * (m10 * m32 - m30 * m12) + m02 * (m10 * m31 - m30 * m11));
    adjugate[3] = -(m01 * (m12 * m23 - m22 * m13) - m02 * (m11 * m23 - m21 * m13) + m03 * (m11 * m22 - m21 * m12));
    adjugate[7] = m00 * (m12 * m23 - m22 * m13) - m02 * (m10 * m23 - m20 * m13) + m03 * (m10 * m22 - m20 * m12);
    adjugate[11] = -(m00 * (m11 * m23 - m21 * m13) - m01 * (m10 * m23 - m20 * m13) + m03 * (m10 * m21 - m20 * m11));
    adjugate[15] = m00 * (m11 * m22 - m21 * m12) - m01 * (m10 * m22 - m20 * m12) + m02 * (m10 * m21 - m20 * m11);
}

float FUN_00192290(const float *m) {
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

void igMatrix44f_GetQuaternion(float *q, float *m) {
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

void FUN_00192810(const float *arg0, float *arg1) {
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

/* Writes the rotation part of the matrix of unit quaternion q.
 * matching construct: declaration-order sweep — the locals' declaration order sets their registers */
void Quaternion_GetRotation(const float *q, float *m) {
    float y2;
    float x2;
    float w;
    float wx;
    float wy;
    float wz;
    float x;
    float xx;
    float xy;
    float zz;
    float z2;
    float xz;
    float yy;
    float y;
    float z;
    float yz;

    x = q[0];
    y = q[1];
    z = q[2];
    w = q[3];
    x2 = 2.0f * x;
    y2 = 2.0f * y;
    z2 = 2.0f * z;
    wx = x2 * w;
    xx = x2 * x;
    wy = y2 * w;
    wz = z2 * w;
    xy = y2 * x;
    xz = z2 * x;
    zz = z2 * z;
    yy = y2 * y;
    yz = z2 * y;
    m[0] = 1.0f - (yy + zz);
    m[1] = xy - wz;
    m[2] = xz + wy;
    m[4] = xy + wz;
    m[5] = 1.0f - (xx + zz);
    m[6] = yz - wx;
    m[8] = xz - wy;
    m[9] = yz + wx;
    m[10] = 1.0f - (xx + yy);
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

void Quaternion_Lerp(float *out, float t, const float *from, const float *to) {
    float toX, toY, toZ, toW;
    float scale;
    if (from[0] * to[0] + from[1] * to[1] + from[2] * to[2] + from[3] * to[3] < 0.0f) {
        toX = -1.0f * to[0];
        toY = -1.0f * to[1];
        toZ = -1.0f * to[2];
        toW = -1.0f * to[3];
    } else {
        toX = to[0];
        toY = to[1];
        toZ = to[2];
        toW = to[3];
    }
    scale = 1.0f - t;
    out[0] = scale * from[0] + t * toX;
    out[1] = scale * from[1] + t * toY;
    out[2] = scale * from[2] + t * toZ;
    out[3] = scale * from[3] + t * toW;
    {
        float inv = 1.0f / quatLength(out);
        out[0] *= inv;
        out[1] *= inv;
        out[2] *= inv;
        out[3] *= inv;
    }
}

void FUN_00192dd0(float *arg0, const float *arg1, const float *arg2) {
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

void Vec3f_CrossInPlace(float *arg0, const float *arg1) {
    float b0; float a0; float b1; float a2; float b2; float a1;
    b2 = arg1[2]; a1 = arg0[1]; a0 = arg0[0]; b1 = arg1[1]; a2 = arg0[2]; b0 = arg1[0];
    arg0[0] = a1 * b2 - a2 * b1;
    arg0[1] = a2 * b0 - a0 * b2;
    arg0[2] = a0 * b1 - a1 * b0;
}

enum Octant {
    OCTANT_XPOS_YPOS_ZPOS,
    OCTANT_XPOS_YPOS_ZNEG,
    OCTANT_XPOS_YNEG_ZPOS,
    OCTANT_XPOS_YNEG_ZNEG,
    OCTANT_XNEG_YPOS_ZPOS,
    OCTANT_XNEG_YPOS_ZNEG,
    OCTANT_XNEG_YNEG_ZPOS,
    OCTANT_XNEG_YNEG_ZNEG
};

int Vec3_GetOctant(const float *normal) {
    Octant octant;
    if (normal[0] < 0.0f) {
        if (normal[1] < 0.0f) octant = normal[2] < 0.0f ? OCTANT_XNEG_YNEG_ZNEG : OCTANT_XNEG_YNEG_ZPOS;
        else octant = normal[2] < 0.0f ? OCTANT_XNEG_YPOS_ZNEG : OCTANT_XNEG_YPOS_ZPOS;
    } else {
        if (normal[1] < 0.0f) octant = normal[2] < 0.0f ? OCTANT_XPOS_YNEG_ZNEG : OCTANT_XPOS_YNEG_ZPOS;
        else octant = normal[2] < 0.0f ? OCTANT_XPOS_YPOS_ZNEG : OCTANT_XPOS_YPOS_ZPOS;
    }
    return octant;
}
