void Vec3_Lerp(void *arg0, float fparg0, void *arg1, void *arg2) {
    float temp_f1;
    float temp_f1_2;
    float temp_f1_3;

    temp_f1 = *(float *)((char *)(arg1) + 0);
    *(float *)((char *)(arg0) + 0) = (float) (temp_f1 + (fparg0 * (*(float *)((char *)(arg2) + 0) - temp_f1)));
    temp_f1_2 = *(float *)((char *)(arg1) + 4);
    *(float *)((char *)(arg0) + 4) = (float) (temp_f1_2 + (fparg0 * (*(float *)((char *)(arg2) + 4) - temp_f1_2)));
    temp_f1_3 = *(float *)((char *)(arg1) + 8);
    *(float *)((char *)(arg0) + 8) = (float) (temp_f1_3 + (fparg0 * (*(float *)((char *)(arg2) + 8) - temp_f1_3)));
}

void Vec3f_TransformDirection(float *out, float *v, float *m) {
    float x = v[0];
    float y = v[1];
    float z = v[2];
    out[0] = x * m[0] + y * m[4] + z * m[8];
    out[1] = x * m[1] + y * m[5] + z * m[9];
    out[2] = x * m[2] + y * m[6] + z * m[10];
}

void FUN_00192fc0(float *out, float *v, float *m) {
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
    Vec3_Lerp(&v1, t, p1, p2);
    Vec3_Lerp(&v2, t, p2, p3);
    Vec3_Lerp(&v3, t, p3, p4);
    Vec3_Lerp(&v4, t, &v1, &v2);
    Vec3_Lerp(&v5, t, &v2, &v3);
    Vec3_Lerp(out, t, &v4, &v5);
}

