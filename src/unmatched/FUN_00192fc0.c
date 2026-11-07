typedef struct { unsigned int mant : 23; unsigned int exp : 8; unsigned int sign : 1; } FB;
static inline float fabs_(float x) { ((FB *)&x)->sign = 0; return x; }
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
