class T { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual void d24(); virtual void d25(); virtual void d26(); virtual void d27(); virtual void d28(); virtual void d29(); virtual void d30(); virtual void d31(); virtual void d32(); virtual void d33(); virtual void d34(); virtual void d35(); virtual void d36(); virtual void d37(); virtual void d38(); virtual void d39(); virtual void d40(); virtual void d41(); virtual void d42(); virtual void d43(); virtual void d44(); virtual void d45(); virtual void d46(); virtual void d47(); virtual int m200(int, int, ...); virtual int m204(int, int, ...); };
struct O { char pad24[24]; T *p; };
extern "C" void FUN_0015d880(O *arg0, int arg1, int arg2, float *arg3) {
    float v[2];
    int base;
    int i2, i1;
    unsigned char z;
    if (arg1 == 0) {
        base = arg2 * 6;
        arg0->p->m200(0, base);
    } else {
        base = arg2 * 6;
        arg0->p->m200(0, base + 3);
    }
    i2 = base + 2;
    arg0->p->m204(0, i2, v);
    z = !arg1;
    v[z] = arg3[z];
    arg0->p->m200(0, i2, v);
    arg0->p->m200(0, base + 4, v);
    i1 = base + 1;
    arg0->p->m204(0, i1, v);
    v[arg1] = arg3[arg1];
    arg0->p->m200(0, i1, v);
    arg0->p->m200(0, base + 5, v);
}
