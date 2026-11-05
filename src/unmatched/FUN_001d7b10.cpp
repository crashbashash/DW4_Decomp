extern "C" {
void FUN_001d7b10(void *arg0, void *arg1);
}
class DW4VCSR_128_0 { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual void d24(); virtual void d25(); virtual void d26(); virtual void d27(); virtual void d28(); virtual void d29(); virtual int vX(float *); };
void FUN_001d7b10(void *arg0, void *arg1) {
    float v[4];
    float *s = (float *)arg1;
    float *d = (float *)arg0;
    d[28] = s[0];
    d[29] = s[1];
    d[30] = s[2];
    d[31] = s[3];
    v[3] = s[3];
    v[0] = 0.0f;
    v[1] = 0.0f;
    v[2] = 0.0f;
    ((DW4VCSR_128_0 *)(*(void **)((char *)arg0 + 204)))->vX(v);
}
