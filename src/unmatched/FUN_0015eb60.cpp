extern "C" {
unsigned char FUN_0015eb60(int *arg0, int arg1, int arg2);
}
class VC { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual int * vX(); };
unsigned char FUN_0015eb60(int *arg0, int arg1, int arg2) {
    int s0 = arg0[9];
    int *p = ((VC *)arg0)->vX();
    unsigned int m = (unsigned int)(*p & 0xF0) >> 4;
    return *(unsigned char *)(s0 + arg1 + arg2 * (m & 0xFF));
}
