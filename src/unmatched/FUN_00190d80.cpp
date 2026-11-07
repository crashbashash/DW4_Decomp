class ScaleVec { public: float _v[3]; float operator[](int i) const { return _v[i]; } };
extern "C" void FUN_00190d80(float *m, const ScaleVec &v) {
    m[0] *= v[0];
    m[1] *= v[1];
    m[2] *= v[2];
    m[4] *= v[0];
    m[5] *= v[1];
    m[6] *= v[2];
    m[8] *= v[0];
    m[9] *= v[1];
    m[10] *= v[2];
    m[12] *= v[0];
    m[13] *= v[1];
    m[14] *= v[2];
}
