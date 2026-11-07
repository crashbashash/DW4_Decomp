void FUN_00181810(float *a, float *b, float *c, float s) {
    float t1;
    float u1;
    float t0;
    float u0;
    u1 = b[1];
    u0 = b[0];
    t0 = c[0];
    t1 = c[1];
    t0 = t0 * s;
    t1 = t1 * s;
    u0 = u0 + t0;
    u1 = u1 + t1;
    a[0] = u0;
    a[1] = u1;
}
