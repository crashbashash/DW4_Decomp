namespace Gap {
namespace Sg {

void igTransformSequence::setMatrix(int index, const igMatrix44f *matrix) {
    float (*m)[4] = (float (*)[4])matrix;
    float rot[4][4];
    float inv[3];
    float *t;
    float *s;
    int i;
    t = ((TransformSampleView *)this)->_xlateList->_data[index];
    t[0] = m[3][0];
    t[1] = m[3][1];
    t[2] = m[3][2];
    s = ((TransformSampleView *)this)->_scaleList->_data[index];
    for (i = 0; i < 3; i++) {
        float *r = m[i];
        s[i] = sqrtf(r[0] * r[0] + r[1] * r[1] + r[2] * r[2]);
    }
    igMatrix44f_Copy(rot[0], m[0]);
    if (FUN_00192290((const float *)m) < 0.0f) {
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
    FUN_00190cb0((float *)rot, inv);
    igMatrix44f_GetQuaternion(((TransformSampleView *)this)->_quatList->_data[index], (float *)rot);
}

void igTransformSequence::getMatrix(int index, igMatrix44f *matrix) const {
    igVec3f rotated;
    float f22, f21, f20;
    int idx;
    igVec3f *v;
    FUN_00192810((const float *)((char *)_quatList->_data + index * 16), matrix->m);
    idx = index * 12;
    v = (igVec3f *)((char *)_xlateList->_data + idx);
    f22 = v->vec[0];
    f21 = v->vec[1];
    f20 = v->vec[2];
    if (_centerOfRotation.vec[0] == 0.0f && _centerOfRotation.vec[1] == 0.0f && _centerOfRotation.vec[2] == 0.0f) {
    } else {
        Vec3f_TransformDirection(rotated.vec, _centerOfRotation.vec, matrix->m);
        f22 = f22 - rotated.vec[0];
        f21 = f21 - rotated.vec[1];
        f20 = f20 - rotated.vec[2];
        f22 = f22 + _centerOfRotation.vec[0];
        f21 = f21 + _centerOfRotation.vec[1];
        f20 = f20 + _centerOfRotation.vec[2];
    }
    matrix->m[12] = f22;
    matrix->m[13] = f21;
    matrix->m[14] = f20;
    FUN_00190cb0(matrix->m, (const float *)((char *)_scaleList->_data + idx));
}

bool igTransformSequence::isTransformable() const {
    return !(_centerOfRotation.vec[0] != g_vec3Zero[0] || _centerOfRotation.vec[1] != DAT_004e105c[0] ||
             _centerOfRotation.vec[2] != DAT_004e1060[0]);
}

void igTransformSequence::transform(const igMatrix44f &matrix)
{
    int count = getKeyFrameCount();
    for (int i = 0; i < count; i++) {
        float key[16];
        igMatrix44f_SetIdentity(key);
        getMatrix(i, (igMatrix44f *)key);
        igMatrix44f_Multiply(key, key, matrix.m);
        setMatrix(i, (const igMatrix44f *)key);
        _centerOfRotation.vec[0] = g_vec3Zero[0];
        _centerOfRotation.vec[1] = DAT_004e105c[0];
        _centerOfRotation.vec[2] = DAT_004e1060[0];
    }
}
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
        v = arg0 - r * arg1;
        DAT_00562a30[0] = v;
        *arg2 = v;
        DAT_00562a28[0] = (int)r;
    }
    return DAT_00562a28[0];
}

