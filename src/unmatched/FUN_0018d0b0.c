typedef struct { float p0, p4, f8, f12, f16, f20; } V;
void FUN_0018d0b0(V *a, float *b) {
    float t = b[0] * a->f8 + b[1] * a->f12 + b[2] * a->f16;
    if (a->f20 < t) a->f20 = t;
}
