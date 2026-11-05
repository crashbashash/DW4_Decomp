void FUN_00181df0(float *o, float *a, float *b, float *c, float x, float y) {
    float u1 = b[1]*x, u0 = b[0]*x;
    float t1 = a[1] + u1 + c[1]*y;
    float t0 = a[0] + u0 + c[0]*y;
    o[0] = t0; o[1] = t1; }
