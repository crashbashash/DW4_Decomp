extern "C" { int FUN_004553e0(void **arg0, unsigned short *arg1); }
class VC100 { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual int vX(int); };
int FUN_004553e0(void **arg0, unsigned short *arg1) {
    int sum;
    unsigned short *p;
    int c;
    p = arg1;
    sum = 0;
    while ((c = *p) != 0) {
        sum += ((VC100 *)arg0)->vX(c);
        p += 1;
    }
    return sum;
}
