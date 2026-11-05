void FUN_00181810(float *a, float *b, float *c, float s) {
    float t0 = c[0] * s;
    float t1 = c[1] * s;
    float u0 = b[0] + t0;
    float u1 = b[1] + t1;
    a[0] = u0;
    a[1] = u1;
}
