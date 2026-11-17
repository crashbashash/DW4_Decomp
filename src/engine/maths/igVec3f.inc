void Vec3_Lerp(float *out, float t, const float *from, const float *to) {
    float start;

    start = from[0];
    out[0] = start + t * (to[0] - start);
    start = from[1];
    out[1] = start + t * (to[1] - start);
    start = from[2];
    out[2] = start + t * (to[2] - start);
}

void Vec3f_TransformDirection(float *out, const float *v, const float *m) {
    float x = v[0];
    float y = v[1];
    float z = v[2];
    out[0] = x * m[0] + y * m[4] + z * m[8];
    out[1] = x * m[1] + y * m[5] + z * m[9];
    out[2] = x * m[2] + y * m[6] + z * m[10];
}

void Vec3f_TransformProjective(float *out, const float *v, const float *m) {
    float x = v[0], y = v[1], z = v[2];
    float w;
    out[0] = m[12] + (x * m[0] + y * m[4] + z * m[8]);
    out[1] = m[13] + (x * m[1] + y * m[5] + z * m[9]);
    out[2] = m[14] + (x * m[2] + y * m[6] + z * m[10]);
    w = m[15] + (x * m[3] + y * m[7] + z * m[11]);
    if (w != 1.0f) {
        float inv;
        if (fabs_(w) < 5e-7f) w = 5e-7f;
        inv = 1.0f / w;
        out[0] *= inv; out[1] *= inv; out[2] *= inv;
    }
}

void FUN_001930f0(struct CurvePoint4 *out, struct CurvePoint4 *p1, struct CurvePoint4 *p2, struct CurvePoint4 *p3, struct CurvePoint4 *p4, float t) {
    struct CurvePoint4 v1, v2, v3, v4, v5;
    Vec3_Lerp(&v1.x, t, &p1->x, &p2->x);
    Vec3_Lerp(&v2.x, t, &p2->x, &p3->x);
    Vec3_Lerp(&v3.x, t, &p3->x, &p4->x);
    Vec3_Lerp(&v4.x, t, &v1.x, &v2.x);
    Vec3_Lerp(&v5.x, t, &v2.x, &v3.x);
    Vec3_Lerp(&out->x, t, &v4.x, &v5.x);
}

