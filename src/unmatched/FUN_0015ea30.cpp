extern "C" {
void FUN_0015ea30(int *arg0);
}
class VC { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual int * vX(); };
void FUN_0015ea30(int *arg0) {
    unsigned int n;
    int base;
    unsigned int i;
    unsigned int j;
    unsigned int off;
    float sum;
    float r;
    int *p = ((VC *)arg0)->vX();
    n = ((unsigned int)(*p & 0xF0) >> 4) & 0xFF;
    if (n != 0) {
        base = arg0[8];
        for (i = 0; i < (unsigned int)arg0[3]; i++) {
            off = i * n;
            sum = 0.0f;
            for (j = 0; j + 1 < n; j++) {
                sum += ((float *)base)[j + off];
            }
            r = 1.0f - sum;
            if (r < 0.0f) {
                r = 0.0f;
            }
            ((float *)base)[n + off - 1] = r;
        }
    }
}
