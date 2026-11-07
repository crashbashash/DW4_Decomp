int Matrix44_Copy();
struct TransformPairView { char p0[12]; unsigned char f12; unsigned char f13; };
static inline int InRange(float x, float lo, float hi) {
    return x >= lo && x <= hi;
}
void FUN_001419f0(struct TransformPairView *arg0, float *m, void *arg2) {
    if (InRange(m[0], 0.999999f, 1.000001f) &&
        InRange(m[1], -0.000001f, 0.000001f) &&
        InRange(m[2], -0.000001f, 0.000001f) &&
        InRange(m[3], -0.000001f, 0.000001f) &&
        InRange(m[4], -0.000001f, 0.000001f) &&
        InRange(m[5], 0.999999f, 1.000001f) &&
        InRange(m[6], -0.000001f, 0.000001f) &&
        InRange(m[7], -0.000001f, 0.000001f) &&
        InRange(m[8], -0.000001f, 0.000001f) &&
        InRange(m[9], -0.000001f, 0.000001f) &&
        InRange(m[10], 0.999999f, 1.000001f) &&
        InRange(m[11], -0.000001f, 0.000001f) &&
        InRange(m[12], -0.000001f, 0.000001f) &&
        InRange(m[13], -0.000001f, 0.000001f) &&
        InRange(m[14], -0.000001f, 0.000001f) &&
        InRange(m[15], 0.999999f, 1.000001f)) {
        arg0->f12 = 1;
    } else {
        arg0->f12 = 0;
    }
    Matrix44_Copy((char *)arg0 + 28, m);
    Matrix44_Copy((char *)arg0 + 92, arg2);
    arg0->f13 = 1;
}
