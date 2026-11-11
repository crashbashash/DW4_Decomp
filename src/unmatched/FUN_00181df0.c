static inline void scale(float *r, const float *v, float s) { r[0] = v[0]*s; r[1] = v[1]*s; }
void FUN_00181df0(float *o, float *a, float *b, float *c, float x, float y) {
    /* matching construct: manual trial — b*x through an inline helper takes f5/f2, a[] f4/f1 */
    float u[2];
    float t0, t1;
    scale(u, b, x);
    t0 = a[0] + u[0] + c[0]*y;
    t1 = a[1] + u[1] + c[1]*y;
    o[0] = t0; o[1] = t1; }
