class ScaleVec { public: float _v[3]; float operator[](int i) const { return _v[i]; } };
extern "C" void FUN_00190b30(float *m, const ScaleVec &v) {
    m[0] += m[3] * v[0];
    m[1] += m[3] * v[1];
    m[2] += m[3] * v[2];
    m[4] += m[7] * v[0];
    m[5] += m[7] * v[1];
    m[6] += m[7] * v[2];
    m[8] += m[11] * v[0];
    m[9] += m[11] * v[1];
    m[10] += m[11] * v[2];
    m[12] += m[15] * v[0];
    m[13] += m[15] * v[1];
    m[14] += m[15] * v[2];
}
